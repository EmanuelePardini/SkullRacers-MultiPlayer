// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BallPawn.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CONSEGNA03_PARDINI_API IInteractionInterface
{
	GENERATED_BODY()
	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(ABallPawn* InteractingPawn = nullptr){};
	virtual void EndInteract(ABallPawn* InteractingPawn = nullptr){};
	UFUNCTION(BlueprintImplementableEvent)
	void OnBeginInteract(ABallPawn* InteractingPawn = nullptr);
	UFUNCTION(BlueprintImplementableEvent)
	void OnEndInteract(ABallPawn* InteractingPawn = nullptr);
};
