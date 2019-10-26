// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspicious,

	Alerted, 

	Walk
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nav")
	class ATargetPoint* Point1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nav")
	class ATargetPoint* Point2;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator originalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	UFUNCTION()
	void ResetOrientation();

	EAIState GuardState;

	void SetGuardState(EAIState newState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState newState);


	bool bMoveToPoint1;
	void MoveToPoint1();

	bool bMoveToPoint2;
	void MoveToPoint2();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
