// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComp;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile spawn point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void APawnBase::RotateTurret(FVector _lookAtTarget)
{
	FVector lookAtTargetCleaned = FVector(_lookAtTarget.X, _lookAtTarget.Y, turretMesh->GetComponentLocation().Z);
	FVector startLocation = turretMesh->GetComponentLocation();
	FRotator turretRotation = FVector(lookAtTargetCleaned - startLocation).Rotation();

	turretMesh->SetWorldRotation(turretRotation);
}

void APawnBase::Fire()
{

}

void APawnBase::HandleDestruction()
{

}



