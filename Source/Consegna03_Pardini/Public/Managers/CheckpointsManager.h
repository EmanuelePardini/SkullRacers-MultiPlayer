// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/CheckPoint.h"
#include "CheckpointsManager.generated.h"

UCLASS()
class CONSEGNA03_PARDINI_API ACheckpointsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointsManager();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ACheckPoint*> CheckPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABallPawn*> Ranks;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setup")
	FString LastLevelId = "End";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateRanks(ABallPawn* ArrivedPawn);
};
