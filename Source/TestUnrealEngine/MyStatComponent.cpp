// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	//틱마다 함수를 실행할 것인가
	PrimaryComponentTick.bCanEverTick = false;
	// InitializeComponent를 실행해 줄 것인가
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}


void UMyStatComponent::SetLevel(int32 SettingLevel)
{
	//싱글톤과 유사하게 게임 인스턴스를 가져옴.
	//캐싱하여 지속적으로 들고 있는 방법이 더 좋을것 같다.
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(SettingLevel);
		if(StatData)
		{
			this->Level = StatData->Level;
			MaxHp = StatData->MaxHp;
			SetHp(StatData->MaxHp);
			Attack = StatData->Attack;
		}
		
	}
}


void UMyStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	Hp = FMath::Clamp(Hp,0,MaxHp);
	
	//리스너 패턴	
	OnHpChanged.Broadcast();
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	int32 NewHp = Hp - DamageAmount;
	SetHp(NewHp);
}



