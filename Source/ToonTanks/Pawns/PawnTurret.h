// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
private:
	FTimerHandle firerateTimerHandle;
	void CheckFireCondition();
	float ReturnDistanceToPlayer();

	APawnTank* PlayerPawn;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, category = "Turret Parameters")
		float fireRate = 0.5f;
	UPROPERTY(EditAnywhere, category = "Turret Parameters")
		float minDistanceToFire = 700;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
};
