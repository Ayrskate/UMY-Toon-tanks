// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameModeBase.h"
#include "Pawns/PawnTank.h"
#include "Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllerBase.h"

void AToonTankGameModeBase::BeginPlay()
{
	HandleGameStart();
	CurrentTime = InitialDefaultTime;
	GetWorld()->GetTimerManager().SetTimer(gameTimeHandle, this, &AToonTankGameModeBase::GameTimer, 1, true);
	gameFinished = false;
}

void AToonTankGameModeBase::GameTimer()
{
	CurrentTime--;
	if(CurrentTime <= 0)
	{
		HandleGameOver(false);
		GetWorld()->GetTimerManager().ClearTimer(gameTimeHandle);
		CurrentTime = 0;
	}
}

void AToonTankGameModeBase::ActorDied(AActor* deadActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("A Pawn died!"));
	if(deadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if(PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if(APawnTurret* destroyedTurret = Cast<APawnTurret>(deadActor))
	{
		destroyedTurret->HandleDestruction();
		TargetTurrets--;
		if(TargetTurrets <= 0)
		{
			TargetTurrets = 0;
			HandleGameOver(true);
		}
	}
}

void AToonTankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	

	GameStart();
	if(PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

int32 AToonTankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> turretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), turretActors);
	return turretActors.Num();
}

void AToonTankGameModeBase::HandleGameOver(bool playerWon)
{
	if(!gameFinished)
	{
		gameFinished = true;
		GameOver(playerWon);
	}
}




