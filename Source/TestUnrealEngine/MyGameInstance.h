// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSave.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FMyCharacterData: public FTableRowBase
{
	GENERATED_BODY()
	FMyCharacterData():Level(99),Attack(99),MaxHp(99) {}
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Level;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Attack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MaxHp;
};

struct FCharacterData;

UCLASS()
class TESTUNREALENGINE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	virtual void Init() override;

	FMyCharacterData* GetStatData(int32 Level);
	FCharacterData* GetCharaterData(int32 Level);

	UPROPERTY()
	TArray<FRaking> Ranking;

public:
	void GetData();
	void SaveData();
	void Test();

private:
	UPROPERTY()
	class UDataTable* Mystats;
	
	UPROPERTY()
	class UDataTable* FCharacterDataStats;
};
