// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskt_GetRandomVector.generated.h"

UCLASS()
class TESTUNREALENGINE_API UBTTaskt_GetRandomVector : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskt_GetRandomVector();
	//테스크가 실행될 경우 행동하는 함수
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
