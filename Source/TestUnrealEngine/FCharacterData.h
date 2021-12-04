// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCharacterData.generated.h"

USTRUCT(BlueprintType)
struct TESTUNREALENGINE_API FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FCharacterData(): Level(1), MaxHp(100.f),Attack(10.f),DropExp(10), NextExp(30){}
	FCharacterData(int32 test): Level(test), MaxHp(100.f),Attack(10.f),DropExp(10), NextExp(30){}
	FCharacterData* GetProperties() { return this; }

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Data")
	int32 Level;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Data")
	float MaxHp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Data")
	float Attack;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Data")
	int32 NextExp;
};
