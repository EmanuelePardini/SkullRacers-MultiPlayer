// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPieces/LevelPieces.h"
#include "ProceduralGenManager.generated.h"

UCLASS()
class CONSEGNA03_PARDINI_API AProceduralGenManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralGenManager();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ALevelPieces*> GeneratedPieces;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<ALevelPieces> LastPiece;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<TSubclassOf<ALevelPieces>> LevelPieces;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int MaxLevelLength = 25;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int MinLevelLength = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Server, Reliable)
	void GenerateLevel();
};
