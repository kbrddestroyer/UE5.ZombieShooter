// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IKWeaponTarget.generated.h"


UCLASS()
class ZOMBIESHOOTER_API AIKWeaponTarget : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
