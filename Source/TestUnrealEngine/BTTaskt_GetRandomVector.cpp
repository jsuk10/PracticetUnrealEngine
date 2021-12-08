// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskt_GetRandomVector.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskt_GetRandomVector::UBTTaskt_GetRandomVector()
{
	//BT에서 보여질 이름설정
	NodeName = TEXT("GetRandomVector");
}

//네비를 이용해 주변의 렌덤 좌표를 찾아오는 함수
EBTNodeResult::Type UBTTaskt_GetRandomVector::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//해당 객체를 가진 폰을 알 수 있음
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	//네비를 통해 갈 수 있는 곳을 한정할 수 있음
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if(NavSystem == nullptr)
		return EBTNodeResult::Failed;
	FNavLocation RandomLocation;

	if(NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector,500.f,RandomLocation))
	{
		//AIController로 이동시키는 함수
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,RandomLocation);
		//블랙보드의 특정 값을 변경하는 함수.
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("RandomVector"),RandomLocation.Location);
		return EBTNodeResult::Succeeded;

	}
	return EBTNodeResult::Failed;

}
