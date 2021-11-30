// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
AMyWeapon::AMyWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEPON"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticWepon(TEXT("StaticMesh'/Game/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));

	if(StaticWepon.Succeeded())
	{
		Weapon->SetStaticMesh(StaticWepon.Object);
	}

	Weapon->SetupAttachment(RootComponent);

	Trigger->SetupAttachment(Weapon);
	
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	Weapon->SetCollisionProfileName(TEXT("MYCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MYCollectible"));
	Trigger->SetBoxExtent(FVector::OneVector * 30);
}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this,&AMyWeapon::OnCharaterOverlap);
}

void AMyWeapon::OnCharaterOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Log,TEXT("GetITem"));
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if(MyCharacter)
	{
		FName WeaponSocket(TEXT("hand_l_Socket"));
		this->AttachToComponent(
			MyCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}
}


