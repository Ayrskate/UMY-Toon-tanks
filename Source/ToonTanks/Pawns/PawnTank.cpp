// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


void APawnTank::CalculateMoveInput(float Value)
{
	moveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float value)
{
	float _rotateAmount = value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator rotation = FRotator(0, _rotateAmount, 0);
	rotationDirection = FQuat(rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(moveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(rotationDirection, true);
}

APawnTank::APawnTank()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	playerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::Fire()
{
	if(BulletsMag > 0)
	{
		Super::Fire();
		BulletsMag--;
		if(BulletsMag <= 0)
		{
			FTimerHandle reloadMagHandle;
			FTimerDelegate reloadMagDelegate = FTimerDelegate::CreateUObject(this,
				&APawnTank::Reload);

			GetWorld()->GetTimerManager().SetTimer(reloadMagHandle, reloadMagDelegate, BulletReloadTime, false);
			UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No more bullets!"));
	}
}

void APawnTank::Reload()
{
	BulletsMag = 5;
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();

	if(playerControllerRef)
	{
		FHitResult traceHitResult;
		playerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, traceHitResult);
		FVector hitLocation = traceHitResult.ImpactPoint;

		RotateTurret(hitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

