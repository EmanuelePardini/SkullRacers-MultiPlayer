// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Increment the timer
	SpawnTimer += DeltaTime;

	// Check if it's time to spawn
	if (SpawnTimer >= SpawnDelay)
	{
		Spawn();
		SpawnTimer = 0.0f; // Reset the timer
	}
}

void ASpawner::Spawn_Implementation()
{
	if(Spawneds.Num() < MaxElements)
	{
		int SpawnableIndex = FMath::RandRange(0,Spawnables.Num()-1);
	
		if (!Spawnables[SpawnableIndex]) return;

		// Get the origin and dimensions of the SpawnBox
		FVector Origin = GetActorLocation();

		// Calculate the opposite points of the box
		FVector MinPoint = Origin - BoxExtent;
		FVector MaxPoint = Origin + BoxExtent;

		
		// Create an FBox using the opposite points of the box
		FBox BoxBounds(MinPoint, MaxPoint);
		
		FVector SpawnLocation = FMath::RandPointInBox(BoxBounds);

		// Spawn the actor at the random location
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Spawnables[SpawnableIndex], SpawnLocation, FRotator::ZeroRotator);
		Spawneds.Add(SpawnedActor);
	}

	//Garbage collection
	for (auto Spawned : Spawneds)
	{
		if(!Spawned) Spawneds.Remove(Spawned);
	}
}

