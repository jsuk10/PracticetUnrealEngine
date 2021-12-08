// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f;
}

//업데이트, 주기적으로 틱을 호출해서 실행함.
//주기는 생성자를 통해 수정
void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto temp = OwnerComp.GetAIOwner();
	auto CurrentPawn = temp->GetPawn();

	if(CurrentPawn == nullptr)
		return;
	
	//월드, 현재 위치, 탐지 범위
	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;

	if(World == nullptr)
		return;

	//결과값
	TArray<FOverlapResult> OverlapResults;
	//찾을 콜리전 쿼리
	FCollisionQueryParams QueryParams(NAME_None,false,CurrentPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams);

	if (bResult)
	{
		for(auto OverlapResult : OverlapResults)
		{
			//플레이어 찾는 함수
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());
			//AI가 제어 하는것이 아닌 플레이어가 제어하는지 판별
			if(MyCharacter && MyCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")),MyCharacter);
				DrawDebugSphere(World,Center,SearchRadius,16,FColor::Magenta,false,0.2f);
				return;
			}
		}
	}else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")),nullptr);
	}
	DrawDebugSphere(World,Center,SearchRadius,16,FColor::Red,false,0.2f);
}
