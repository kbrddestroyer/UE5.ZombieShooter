// CPlayer - Player controller with basic input functionality
// Responsible for moving player
//
// Author: KeyboardDestroyer


#include "CPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CPlayerAnimInstance.h"
#include "WeaponAnimInstance.h"


#define PLAYER_ANIM(default_animator) Cast<UCPlayerAnimInstance>(default_animator)


bool ACPlayer::isValidToAnimate()
{
	return (playerMesh && playerAnimInstance);
}

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	playerMesh = GetComponentByClass<USkeletalMeshComponent>();

	if (!playerMesh)
		return;

	playerAnimInstance = playerMesh->GetAnimInstance();

	if (!playerAnimInstance)
		return;

	Cast<UCPlayerAnimInstance>(playerAnimInstance)->ik_lookTarget = getAimPoint();
}

FVector ACPlayer::getAimPoint() const
{
	FVector location;
	FRotator rotation;

	GetActorEyesViewPoint(location, rotation);
	return location + rotation.Vector() * 2000;
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(iaLook, ETriggerEvent::Triggered, this, &ACPlayer::MoveCamera);
	Input->BindAction(iaMove, ETriggerEvent::Triggered, this, &ACPlayer::MovePlayer);
	Input->BindAction(iaSight, ETriggerEvent::Triggered, this, &ACPlayer::Ironsight);
	Input->BindAction(iaShoot, ETriggerEvent::Triggered, this, &ACPlayer::Shoot);
}

void ACPlayer::MoveCamera(const FInputActionInstance& Instance)
{
	FVector2D inputData = Instance.GetValue().Get<FVector2D>() * fMouseSens;

	AddControllerYawInput(inputData.X);
	AddControllerPitchInput(inputData.Y);
	USkeletalMeshComponent* mesh = GetComponentByClass<USkeletalMeshComponent>();

	if (isValidToAnimate())
		PLAYER_ANIM(playerAnimInstance)->ik_lookTarget = getAimPoint();
}

void ACPlayer::MovePlayer(const FInputActionInstance& Instance)
{
	FVector2D inputData = Instance.GetValue().Get<FVector2D>();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation = FRotator(0, rotation.Yaw, 0);

	const FVector forward = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector right = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(right, inputData.X);
	AddMovementInput(forward, inputData.Y);
	
	if (isValidToAnimate())
	{
		PLAYER_ANIM(playerAnimInstance)->ik_lookTarget = getAimPoint();
		PLAYER_ANIM(playerAnimInstance)->playerSpeed = inputData;
	}
}

void ACPlayer::Ironsight(const FInputActionInstance& Instance)
{
	if (isValidToAnimate())
		PLAYER_ANIM(playerAnimInstance)->bIronsight = Instance.GetValue().Get<bool>();
}

void ACPlayer::Shoot(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("invoke shooting"));

	if (!weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot invoke shooting"));
		return;
	}

	UWeaponAnimInstance* weaponAnim = Cast<UWeaponAnimInstance>(weapon->GetAnimInstance());
	weaponAnim->shoot = Instance.GetValue().Get<bool>();
}
