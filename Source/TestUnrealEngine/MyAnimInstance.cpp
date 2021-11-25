// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if(Isvalid(pawn))
	{

		speed = pawn->GetVelocity().Size();
	}

}