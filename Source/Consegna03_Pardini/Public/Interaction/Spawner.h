// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class CONSEGNA03_PARDINI_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpawnDelay = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpawnTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<TSubclassOf<AActor>> Spawnables;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> Spawneds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FVector BoxExtent = FVector(500,500,1);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int MaxElements = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Reliable,Server)
	void Spawn();
};
