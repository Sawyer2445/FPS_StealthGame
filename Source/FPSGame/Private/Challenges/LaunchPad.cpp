// Fill out your copyright notice in the Description page of Project Settings.P

#include "Public/Challenges/LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75.0f, 75.0f, 50.0f));
	RootComponent = OverlapComp;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::Launch);

	LaunchAngle = 70.0f;
	LaunchStrenght = 2000.0f;
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaunchPad::Launch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FRotator PadRotator = GetActorRotation();
	PadRotator.Pitch += LaunchAngle;
	FVector LaunchVel = PadRotator.Vector() * LaunchStrenght;

	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character)
	{
		UE_LOG(LogTemp, Log, TEXT("Overlaped with LaunchPAd !"));
		Character->LaunchCharacter(LaunchVel, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX,GetActorLocation());
	}

	if (OtherComp->IsSimulatingPhysics() && OtherComp)
	{
		UE_LOG(LogTemp, Log, TEXT("Overlaped box with LaunchPAd !"));
		OtherComp->AddImpulse(LaunchVel, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
	}
	
}
