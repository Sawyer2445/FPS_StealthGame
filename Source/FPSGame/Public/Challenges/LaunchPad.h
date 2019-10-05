// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Comonents")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Comonents")
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* LaunchFX;

	UPROPERTY(EditInstanceOnly, Category = "Launch")
	float LaunchAngle;

	UPROPERTY(EditInstanceOnly, Category = "Launch")
	float LaunchStrenght;

	UFUNCTION()
	void Launch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
