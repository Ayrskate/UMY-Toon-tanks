// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameModeBase.generated.h"


class APawnTurret;
class APawnTank;
class APlayerControllerBase;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank;
	
	APlayerControllerBase* PlayerControllerRef;
	FTimerHandle gameTimeHandle;

	bool gameFinished = false;
	int32 GetTargetTurretCount();
	void HandleGameOver(bool playerWon);
	void HandleGameStart();

public:

	void ActorDied(AActor* deadActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Time")
		float InitialDefaultTime = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Time")
		float CurrentTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turrets left")
		int32 TargetTurrets = 0;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Came Loop")
	int32 StartDelay = 0;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool playerWon);

	void GameTimer();
};
