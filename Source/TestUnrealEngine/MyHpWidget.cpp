// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHpWidget.h"

#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyHpWidget::BindHp(UMyStatComponent* StatComp)
{
	//meta를 사용하지 않고 바인드 시켜주는 방법!
	//PB_HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_hpBar")));
	CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this, &UMyHpWidget::UpdateHp);

}

void UMyHpWidget::UpdateHp()
{
	if(CurrentStatComp.IsValid())
	PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());	
}
