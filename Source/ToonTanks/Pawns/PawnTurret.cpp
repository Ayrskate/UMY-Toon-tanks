// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(firerateTimerHandle, this, &APawnTurret::CheckFireCondition, fireRate, true);

	PlayerPawn = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn) 
	{
		return;
	}

	if (ReturnDistanceToPlayer() <= minDistanceToFire) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if(!PlayerPawn)
	{
		return 0.0f;
	}

	FVector playerPosition = PlayerPawn->GetActorLocation();
	float distance = FVector::Dist(playerPosition, GetActorLocation());

	return distance;
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerPawn && ReturnDistanceToPlayer() <= minDistanceToFire)
	{
		RotateTurret(PlayerPawn->GetActorLocation());
	}
}

