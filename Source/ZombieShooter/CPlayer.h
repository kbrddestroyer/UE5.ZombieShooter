// CPlayer - Player controller with basic input functionality
// Responsible for moving player
//
// Author: KeyboardDestroyer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputMappingContext.h"

#include "CPlayer.generated.h"


#define USE_DEBUG

UCLASS()
class ZOMBIESHOOTER_API ACPlayer : public ACharacter
{
	GENERATED_BODY()
public:
#pragma region INPUT_ACTIONS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* iaLook = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* iaMove = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* iaSight = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* iaShoot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* DefaultMappingContext = nullptr;
#pragma endregion

#pragma region ADJUSTMENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float fMouseSens = 1.0;

	UPROPERTY(EditAnywhere, Category = "Debug")
	float fDebugMessageLifetime = .5f;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* weapon;

public:
	// Sets default values for this character's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector getAimPoint() const;
public:
	UFUNCTION()
	void MoveCamera(const FInputActionInstance& Instance);

	UFUNCTION()
	void MovePlayer(const FInputActionInstance& Instance);

	UFUNCTION()
	void Ironsight(const FInputActionInstance& Instance);

	UFUNCTION()
	void Shoot(const FInputActionInstance& Instance);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
