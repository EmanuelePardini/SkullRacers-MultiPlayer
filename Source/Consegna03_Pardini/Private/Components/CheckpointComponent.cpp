// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CheckpointComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCheckpointComponent::UCheckpointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCheckpointComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* CPMActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACheckpointsManager::StaticClass());
	CheckpointsManager = Cast<ACheckpointsManager>(CPMActor);
}


// Called every frame
void UCheckpointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCheckpointComponent::Increment(ACheckPoint* PassedCheckPoint)
{
	//Check if is a new Checkpoint
	if(this && !PassedCheckPoints.IsEmpty())
	{
		for (auto CheckPoint : PassedCheckPoints)
		{
			if(CheckPoint == PassedCheckPoint) return;
		}
	}

	//Update Passed Checkpoints
	if(PassedCheckPoint) PassedCheckPoints.Add(PassedCheckPoint);


	//Check if is last checkpoint of the match
	if(CheckpointsManager)
	{
		if(PassedCheckPoints.Last()->Id == CheckpointsManager->LastLevelId)
		{
			ABallPawn* BallPawn = Cast<ABallPawn>(GetOwner());
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,"Finished");
			CheckpointsManager->UpdateRanks(BallPawn);
		}
	}
}

