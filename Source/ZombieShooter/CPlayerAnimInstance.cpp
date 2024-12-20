#include "CPlayerAnimInstance.h"
#include "CPlayerAnimInstance.h"
#include "CPlayerAnimInstance.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerAnimInstance.h"


FVector2D UCPlayerAnimInstance::getPlayerSpeed() { return playerSpeed; }

void UCPlayerAnimInstance::setPlayerSpeed(FVector2D speed)
{
	playerSpeed = speed;
}

bool UCPlayerAnimInstance::isIronsight()
{
	return bIronsight;
}

void UCPlayerAnimInstance::setIronsight(bool state)
{
	bIronsight = state;
}
