// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ProceduralGenManager.h"

#include "LevelPieces/LevelPieces.h"

// Sets default values
AProceduralGenManager::AProceduralGenManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProceduralGenManager::BeginPlay()
{
	Super::BeginPlay();
	GenerateLevel();
}

// Called every frame
void AProceduralGenManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralGenManager::GenerateLevel_Implementation()
{
	int RandIndex;
	int LevelLength = FMath::RandRange(MinLevelLength,MaxLevelLength);
	FVector SpawnLoc;
	FRotator SpawnRot;
	AActor* NewActorPiece;
	
	for(int i = 0; i < LevelLength; i++)
	{

		if(GeneratedPieces.Num() > 0)
		{
			RandIndex = FMath::RandRange(0, LevelPieces.Num()-1);
			SpawnLoc = GeneratedPieces.Last()->AnchorPoint->GetComponentLocation();
			SpawnRot = GeneratedPieces.Last()->GetActorRotation();
			NewActorPiece = GetWorld()->SpawnActor(LevelPieces[RandIndex], &SpawnLoc, &SpawnRot);
		}
		else
		{
			SpawnLoc = GetActorLocation();
			SpawnRot = GetActorRotation();
			NewActorPiece = GetWorld()->SpawnActor(LevelPieces[0], &SpawnLoc, &SpawnRot);
		}
		ALevelPieces* NewPiece = Cast<ALevelPieces>(NewActorPiece);
		GeneratedPieces.Add(NewPiece);
	}

	
	if(!LastPiece) return;
	//Last level piece generation
	SpawnLoc = GeneratedPieces.Last()->AnchorPoint->GetComponentLocation();
	SpawnRot = GeneratedPieces.Last()->GetActorRotation();
	NewActorPiece = GetWorld()->SpawnActor(LastPiece, &SpawnLoc, &SpawnRot);
	ALevelPieces* NewPiece = Cast<ALevelPieces>(NewActorPiece);
	GeneratedPieces.Add(NewPiece);
}

