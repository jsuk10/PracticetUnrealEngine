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
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Pwan", Meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Pwan", Meta=(AllowPrivateAccess=true))
	bool IsFalling;
};
