// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHpWidget.generated.h"

UCLASS()
class TESTUNREALENGINE_API UMyHpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMyStatComponent* StatComp);
	void UpdateHp();

private:
	//위젯을 자동 바인드 해줌.
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;
	//이방식보다는 인자 있는 델리게이트가 더 좋음.
	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;
};
