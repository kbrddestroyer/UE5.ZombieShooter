#include "IKWeaponTarget.h"
#include "CPlayerAnimInstance.h"


void AIKWeaponTarget::BeginPlay()
{
	Super::BeginPlay();
}

void AIKWeaponTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	USkeletalMeshComponent* mesh = FindComponentByClass<USkeletalMeshComponent>();

	if (!mesh)
		return;

	UCPlayerAnimInstance* animation = Cast<UCPlayerAnimInstance>(mesh->GetAnimInstance());

	if (!animation)
		return;

	// animation->ik_lookTarget = GetTargetLocation();
}
