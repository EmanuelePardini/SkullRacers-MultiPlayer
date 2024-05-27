// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactables.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA03_PARDINI_API ACoin : public AInteractables
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	int Value = 10;
	
	virtual void Interact(ABallPawn* InteractingPawn) override;
};
