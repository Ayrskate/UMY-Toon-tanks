// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	gameModeRef = Cast<AToonTankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//Event Bindings
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float damage, const UDamageType* damageType, AController* instigatedBy, AActor* damageCauser)
{
	if(damage == 0 || Health <= 0) return;

	Health = FMath::Clamp(Health - damage, 0.0f, DefaultHealth);

	if(GetOwner() == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player's health is:%f"), Health));
		//UE_LOG(LogTemp, Warning, TEXT("Player's health is:%i"), Health);
	}

	if(Health <= 0)
	{
		if(gameModeRef)
		{
			gameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health component has no ref to gamemode!"));
		}
	}
}

