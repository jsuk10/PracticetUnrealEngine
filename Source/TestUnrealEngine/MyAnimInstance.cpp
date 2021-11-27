// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AM(TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));	
	if(AM.Succeeded())
		AttackAniMontage = AM.Object;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if(IsValid(pawn))
	{
		Speed = pawn->GetVelocity().Size();
		auto Charater = Cast<ACharacter>(pawn);
		if(Charater)
		{
			IsFalling = Charater->GetMovementComponent()->IsFalling();
		}
	}
}
void UMyAnimInstance::PlayAttackMontage()
{
		Montage_Play(AttackAniMontage,1.f);
}
	