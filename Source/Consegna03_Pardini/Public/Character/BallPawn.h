// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "BallPawn.generated.h"

UCLASS()
class CONSEGNA03_PARDINI_API ABallPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallPawn();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	float MoveForce = 1000.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	float JumpForce = 10000.f;
	
	//Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	UScoreComponent* ScoreComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	class UCheckpointComponent* CheckpointComponent;
	
protected:
	//Boost Management
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float BoostTimer = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	float BoostDelay = 4.f;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float BoostRechargeTimer = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Setup")
	float BoostRechargeDelay = 20.f;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bCanBoost = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsBoosting = false;
	
	//Camera Declaration
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	UCameraComponent* ThirdPersonCamera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	USphereComponent* BallCollider;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	UStaticMeshComponent* BallMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ManageTimers(float DeltaTime);

	//Movement Manager
	void Move(const FInputActionValue& Value);
	
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_Move(FVector Value);
	bool Server_Move_Validate(FVector Value);
	void Server_Move_Implementation(FVector Value);
	
	void Look(const FInputActionValue& Value);

	//Jump Manage
	void DoJump(const FInputActionValue& Value);

	UFUNCTION(Reliable,Server,WithValidation)
	void Server_Jump(FVector Value);
	bool Server_Jump_Validate(FVector Value);
	void Server_Jump_Implementation(FVector Value);

	//Boost Manage
	UFUNCTION(Reliable, Server)
	void Boost(const FInputActionValue& Value);
	UFUNCTION(Reliable, Server)
	void EndBoost();
	UFUNCTION(Reliable, Server)
	void Die();

	//PLAY: For VFX and Audio
	UFUNCTION(BlueprintImplementableEvent)
	void PlayBoost();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDoJump();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDie();

	//Utilities
	bool IsPawnGrounded();
	
};
