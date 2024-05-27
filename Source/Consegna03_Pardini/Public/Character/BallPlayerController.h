// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallPawn.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "BallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA03_PARDINI_API ABallPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UInputMappingContext* IMC;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABallPawn* BallPawn;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UPlayerInputData* InputData;

	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	//Movement Manage
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	//Jump Manage
	void Jump(const FInputActionValue& Value);

	//Boost Manage
	void Boost(const FInputActionValue& Value);
};
