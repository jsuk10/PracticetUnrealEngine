// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MainWidget.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	//DefaultPawnClass = AMyCharacter::StaticClass();
	UE_LOG(LogTemp,Error,TEXT("GameMode"));
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Char(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	static ConstructorHelpers::FClassFinder<UMainWidget>MainWdget(TEXT("WidgetBlueprint'/Game/Blueprints/MainWidget.MainWidget_C'"));
	if(MainWdget.Succeeded())
	{
		MainWidgetClass = MainWdget.Class;

		CurrentWidget = CreateWidget(GetWorld(), MainWidgetClass);
		if(CurrentWidget)
			CurrentWidget->AddToViewport();
	}
}
	