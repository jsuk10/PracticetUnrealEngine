// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Data (TEXT("DataTable'/Game/Data/StatTable.StatTable'"));
	if(Data.Succeeded())
	{
		Mystats = Data.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	
	UE_LOG(LogTemp, Warning, TEXT("Init %d"), GetStatData(1)->Attack);

}

FMyCharacterData* UMyGameInstance::GetStatData(int32 Level)
{
	return Mystats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));
}
