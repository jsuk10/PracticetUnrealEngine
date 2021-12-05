// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMyGameModeBase();

	UPROPERTY()
	TSubclassOf<UUserWidget> MainWidgetClass;
	
	UPROPERTY()
	class UUserWidget* CurrentWidget;
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
