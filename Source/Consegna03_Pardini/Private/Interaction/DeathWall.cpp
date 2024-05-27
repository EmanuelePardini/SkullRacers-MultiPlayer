// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/DeathWall.h"

// Sets default values
ADeathWall::ADeathWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADeathWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathWall::Interact(ABallPawn* InteractingPawn)
{
	Super::Interact(InteractingPawn);
	InteractingPawn->Die();
}
