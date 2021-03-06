// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTUNREALENGINE_API UMyStatComponent : public UActorComponent
{

private:
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:
	int32 GetLevel() const{	return Level; }
	int32 GetAttack() const{ return Attack; }
	int32 GetHp() const{ return Hp; }
	int32 GetMaxHp() const{	return MaxHp;}
	float GetHpRatio() {return Hp/(float)MaxHp;}
	void SetHp(int32 Hp);
	void SetLevel(int32 Level);
	void OnAttacked(float DamageAmount);
private:
	UPROPERTY(EditAnywhere,Category=STAT,Meta=(AllowPrivatAccess = true))
	int32 Level;
	UPROPERTY(EditAnywhere,Category=STAT,Meta=(AllowPrivatAccess = true))
	int32 Attack;
	UPROPERTY(EditAnywhere,Category=STAT,Meta=(AllowPrivatAccess = true))
	int32 Hp;
	UPROPERTY(EditAnywhere,Category=STAT,Meta=(AllowPrivatAccess = true))
	int32 MaxHp;
public:
	FOnHpChanged OnHpChanged;
};
