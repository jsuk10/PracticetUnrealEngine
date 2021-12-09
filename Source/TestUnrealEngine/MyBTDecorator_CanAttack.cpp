

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_CanAttack.h"

#include "AIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTDecorator_CanAttack::UMyBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UMyBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(CurrentPawn == nullptr)
		return false;
	
	auto Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if(Target == nullptr)
		return false;
	
	return Target->GetDistanceTo(CurrentPawn) <= 200.f;
	
}
