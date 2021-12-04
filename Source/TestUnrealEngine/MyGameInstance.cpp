// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "FCharacterData.h"
#include "GameSave.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Data (TEXT("DataTable'/Game/Data/StatTable.StatTable'"));
	if(Data.Succeeded())
	{
		Mystats = Data.Object;
	}

	//컨스트럭터 헬퍼 통해 데이터 파일을 가져온다.
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTER(TEXT("/Game/Data/DataTable.DataTable"));
	if(DT_CHARACTER.Succeeded())
	{
		FCharacterDataStats = DT_CHARACTER.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Init %d"), GetStatData(1)->Attack);
	
	UE_LOG(LogTemp, Warning, TEXT("Init %f"), GetCharaterData(20)->Attack);

}

FMyCharacterData* UMyGameInstance::GetStatData(int32 Level)
{
	return Mystats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));
}

FCharacterData* UMyGameInstance::GetCharaterData(int32 Level)
{
	return FCharacterDataStats->FindRow<FCharacterData>(*FString::FromInt(Level), TEXT(""));
}


void UMyGameInstance::GetData()
{
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	if (SaveGameInstance)
	{
		auto LodaGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SlotName, SaveGameInstance->Index));
		if (LodaGameInstance)
			Ranking = LodaGameInstance->Ranking;
	}
}

void UMyGameInstance::Test()
{
	GetData();

	if (Ranking.Num() > 0)
	{
		for (FRaking a : Ranking)
		{
			UE_LOG(LogTemp, Error, TEXT("Grade : %d"), a.Grade);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Num  = 0"));
	}

	Ranking.Add(FRaking(TEXT("hi"), 500));
	Ranking.Add(FRaking(TEXT("hi2"), 1500));
	Ranking.Add(FRaking(TEXT("hi3"), 5500));

	SaveData();
}

void UMyGameInstance::SaveData()
{
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));

	if (SaveGameInstance)
	{
		SaveGameInstance->Ranking = Ranking;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGameInstance is nullptr"));
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SlotName, SaveGameInstance->Index);
}
