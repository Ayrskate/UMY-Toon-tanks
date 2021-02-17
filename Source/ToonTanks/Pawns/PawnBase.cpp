// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ProjectileBase.h"
#include "ToonTanks/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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

	tankTrailEffectPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Trail point"));
	tankTrailEffectPoint->SetupAttachment(RootComponent);

	tankTrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("trail effect"));
	tankTrailEffect->SetupAttachment(tankTrailEffectPoint);

	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
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
	if(projectileClass)
	{
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectileClass, projectileSpawnPoint->GetComponentLocation(), projectileSpawnPoint->GetComponentRotation());
		tempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, deathParticles,GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(deathShake);
}