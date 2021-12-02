// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* HP;
	/*
	UPROPERTY(meta=(BindWidget))
	class UButton* Button;
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* ProgressBar;
	*/

};
