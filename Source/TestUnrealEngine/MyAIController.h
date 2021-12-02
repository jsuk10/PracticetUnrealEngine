// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	AMyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void RandomMove();
	FTimerHandle TimerHandle;
};
