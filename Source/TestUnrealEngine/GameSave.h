// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

USTRUCT()
struct FRaking
{
	GENERATED_BODY()
	FRaking() {}
	FRaking(FString NewName, int32 NewGrade): Grade(NewGrade), Name(NewName){}
	UPROPERTY()
	int32 Grade;
	UPROPERTY()
	FString Name;
};


UCLASS()
class TESTUNREALENGINE_API UGameSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString SlotName = "Ranking";
	UPROPERTY()
	int32 Index = 1;

	UPROPERTY()
	TArray<FRaking> Ranking;
};
