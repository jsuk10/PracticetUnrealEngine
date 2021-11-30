// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FMyCharacterData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Level;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Attack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MaxHp;
};

UCLASS()
class TESTUNREALENGINE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	virtual void Init() override;

	FMyCharacterData* GetStatData(int32 Level);
		
private:
	UPROPERTY()
	class UDataTable* Mystats;
};
