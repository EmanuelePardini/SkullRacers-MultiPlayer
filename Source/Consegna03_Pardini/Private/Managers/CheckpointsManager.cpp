// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/CheckpointsManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpointsManager::ACheckpointsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckpointsManager::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckPoint::StaticClass(), OutActors);
	
	for (auto OutActor : OutActors)
	{
		ACheckPoint* CheckPoint = Cast<ACheckPoint>(OutActor);
		CheckPoints.Add(CheckPoint);
	}
}

// Called every frame
void ACheckpointsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointsManager::UpdateRanks(ABallPawn* ArrivedPawn)
{
	Ranks.Add(ArrivedPawn);
}

