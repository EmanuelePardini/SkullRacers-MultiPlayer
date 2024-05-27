// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPieces.generated.h"

UCLASS()
class CONSEGNA03_PARDINI_API ALevelPieces : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelPieces();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UStaticMeshComponent* RoadMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UStaticMeshComponent* AnchorPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
