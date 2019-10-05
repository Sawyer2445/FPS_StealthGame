// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlackHoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMesh"));
	BlackHoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BlackHoleMesh;

	firstSphere = CreateDefaultSubobject<USphereComponent>(TEXT("firstSphere"));
	firstSphere->SetupAttachment(BlackHoleMesh);

	// Bind to Event
	firstSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	secondSphere = CreateDefaultSubobject<USphereComponent>(TEXT("secondSphere"));
	secondSphere->SetupAttachment(BlackHoleMesh);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TArray<UPrimitiveComponent*> boxes;
	secondSphere->GetOverlappingComponents(boxes);

	int boxesCount = boxes.Num();
	for (int32 i = 0; i < boxesCount; i++)
	{
		UPrimitiveComponent* box = boxes[i];
		if (box && box->IsSimulatingPhysics())
		{
			box->AddRadialForce(GetActorLocation(), secondSphere->GetScaledSphereRadius(), -2000, ERadialImpulseFalloff::RIF_Constant, true);
		}
		
	}

}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

