// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* camera;

	APlayerController* playerControllerRef;
	bool bIsPlayerAlive = true;

	FVector moveDirection;
	FQuat rotationDirection;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float value);

	void Move();
	void Rotate();

	int32 maxBulletsMag = 15;


public:
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Movement variables")
		float MoveSpeed = 380.0f;
	UPROPERTY(EditAnywhere, Category = "Movement variables")
		float MoveSpeedTurbo = 650.0f;
	UPROPERTY(EditAnywhere, Category = "Movement variables")
		float RotateSpeed = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting parameters")
		int32 BulletsMag = 5;
	UPROPERTY(EditAnywhere, Category = "Shooting parameters")
		float BulletReloadTime = 1.5f;

	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

	bool turboActivated = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire() override;

	void Reload();

	void ActivateTurbo();
	void DectivateTurbo();
};
