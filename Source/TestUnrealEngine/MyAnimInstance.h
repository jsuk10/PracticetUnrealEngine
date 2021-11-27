// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void PlayAttackMontage();
	
private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Pwan", Meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Pwan", Meta=(AllowPrivateAccess=true))
	bool IsFalling;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Pwan", Meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackAniMontage;
};

