// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/AI/BT_Chater.BT_Chater'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("BlackboardData'/Game/AI/BB_Chater.BB_Chater'"));
	if(BD.Succeeded()) BlackBoardData = BD.Object;
	if(BT.Succeeded()) BehaviorTree = BT.Object;

}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetPawn(InPawn);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyAIController::RandomMove,3.f,true);
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	if(UseBlackboard(BlackBoardData,Blackboard) && RunBehaviorTree(BehaviorTree))
	{
		//TODO BlackBoard
	}
}

void AMyAIController::RandomMove()
{
	auto CurrentPawn = GetPawn();
	//UE_LOG(LogTemp,Error,TEXT("move"));

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(NavSystem == nullptr)
		return;
	FNavLocation RandomLocation;

	if(NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector,500.f,RandomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,RandomLocation);
	}
}
