// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticatOnMissionCompeted_Implementation(APawn* InstigatorPawn, bool bMissionSucceed)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSucceed);
			APawn* Pawn = PC->GetPawn();
			if (Pawn && Pawn->IsLocallyControlled())
			{
				Pawn->DisableInput(nullptr);
			}
		} 
	}
}
