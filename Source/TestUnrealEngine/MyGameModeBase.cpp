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
	
	static FAutoConsoleCommand CCmd_HelloWorld(
        TEXT("c.helloworld"),
        TEXT("HelloWorld를 띄워보자"),
        FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Params)
            {
                FString ParamStr;
                for (const FString& Param : Params)
                    ParamStr += Param;
                UE_LOG(LogTemp, Log, TEXT("HeUllo World!! Param : [%s]"), *ParamStr);
            }),
        ECVF_Default);
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Error,TEXT("tmep"));
	static ConstructorHelpers::FClassFinder<UMainWidget>MainWdgets(TEXT("WidgetBlueprint'/Game/Blueprints/MainWidget.MainWidget_C'"));
    
	if(MainWdgets.Succeeded())
	{
		MainWidgetClass = MainWdgets.Class;
    
		CurrentWidget = CreateWidget(AActor::GetWorld(), MainWidgetClass);
		if(CurrentWidget)
			CurrentWidget->AddToViewport();
	}
}


