// CPlayer - Player controller with basic input functionality
// Responsible for moving player
//
// Author: KeyboardDestroyer


#include "CPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(iaLook, ETriggerEvent::Triggered, this, &ACPlayer::MovePlayer);
}

void ACPlayer::MovePlayer(const FInputActionInstance& Instance)
{
	FVector2D inputData = Instance.GetValue().Get<FVector2D>() * fMouseSens;
	AddControllerYawInput(inputData.X);
	AddControllerPitchInput(inputData.Y);
}
