// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TESTUNREALENGINE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool binterrupted);
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	bool IsAttack = false;
	
	UPROPERTY(VisibleAnywhere)
	class UMyAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere)
	int32 AttackIndex = 0;
public:
	//BP에서 얻어올 수 있도록 변수 선언하여 움직일때 갱신해줌
	UPROPERTY(VisibleAnywhere)
	float UpDownValue = 0;
	UPROPERTY(VisibleAnywhere)
	float LeftRightValue= 0 ;
};
