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
	UE_LOG(LogTemp, Warning, TEXT("Instance On!"));
	
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
	UE_LOG(LogTemp, Error, TEXT("test"));
	if (Mystats->IsValidLowLevel())
	{
		Mystats->AddRow(FName("Test3"), FMyCharacterData());
	}
	if (FCharacterDataStats->IsValidLowLevel())
	{
		FCharacterDataStats->AddRow(FName("Test3"), FCharacterData(20));
		FCharacterDataStats->SaveConfig();
	}
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
