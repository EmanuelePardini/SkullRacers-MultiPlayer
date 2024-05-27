// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Coin.h"

void ACoin::Interact(ABallPawn* InteractingPawn)
{
	Super::Interact(InteractingPawn);
	
	InteractingPawn->ScoreComponent->IncrementScore(Value);
	Destroy();
}
