// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_Attack.h"

#include "AIController.h"
#include "MyCharacter.h"

UMyBTTaskNode_Attack::UMyBTTaskNode_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMyBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Charater = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(Charater == nullptr)
		return EBTNodeResult::Failed;

	Charater->Attack();
	bIsAttacking = true;

	//람다 델리게이트 추가.
	Charater->OnAttackEnd.AddLambda([this]()
	{
		bIsAttacking = false;
	});
	return Result;
}

void UMyBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if(bIsAttacking == false)
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);

}
