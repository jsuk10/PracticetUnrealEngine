// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"
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
		auto Charater = Cast<AMyCharacter>(pawn);
		if(Charater)
		{
			IsFalling = Charater->GetMovementComponent()->IsFalling();
			Virtical = Charater->UpDownValue;
			Horizontal = Charater->LeftRightValue;
		}
	}
}
void UMyAnimInstance::PlayAttackMontage()
{
		Montage_Play(AttackAniMontage,1.f);
}

void UMyAnimInstance::JumpToSection(int32 Section)
{
	//인덱스를 통해 섹션을 알아냄
	FName Name = GetAttackMotageName(Section);
	//섹션으로 건너뜀
	Montage_JumpToSection(Name, AttackAniMontage);
}

FName UMyAnimInstance::GetAttackMotageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"),SectionIndex));
}


//애니메이션에서 노티를 만들었다.
//노티의 이름과 함수의_이후 이름을 같게 해줄것
//아래 예시는 노티 이름을 AttackHit로 지었다.
void UMyAnimInstance::AnimNotify_AttackHit()
{
	UE_LOG(LogTemp,Log,TEXT("Hit"));
}
	