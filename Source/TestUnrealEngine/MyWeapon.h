// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"



UCLASS()
class TESTUNREALENGINE_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;
	UFUNCTION()
	void OnCharaterOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp,	int32 otherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
};
