// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlRigAnimInstance.h"
#include "CPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API UCPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FVector2D playerSpeed;

	UPROPERTY(BlueprintReadOnly)
	bool bIronsight = false;

public:
	UFUNCTION()
	FVector2D getPlayerSpeed();

	void setPlayerSpeed(FVector2D);

	UFUNCTION()
	bool isIronsight();

	void setIronsight(bool);
};
