// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables.h"
#include "GameFramework/Actor.h"
#include "DeathWall.generated.h"

UCLASS()
class CONSEGNA03_PARDINI_API ADeathWall : public AInteractables
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(ABallPawn* InteractingPawn) override;

};
