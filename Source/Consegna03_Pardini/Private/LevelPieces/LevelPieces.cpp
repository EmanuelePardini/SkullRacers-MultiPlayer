// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPieces/LevelPieces.h"

// Sets default values
ALevelPieces::ALevelPieces()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>("RoadMesh");
	RoadMesh->SetupAttachment(RootComponent);
	AnchorPoint = CreateDefaultSubobject<UStaticMeshComponent>("AnchorPoint");
	AnchorPoint->SetupAttachment(RoadMesh);
}

// Called when the game starts or when spawned
void ALevelPieces::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ALevelPieces::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

