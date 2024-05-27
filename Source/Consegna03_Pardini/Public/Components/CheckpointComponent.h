// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/CheckPoint.h"
#include "Managers/CheckpointsManager.h"
#include "CheckpointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONSEGNA03_PARDINI_API UCheckpointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCheckpointComponent();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ACheckPoint*> PassedCheckPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACheckpointsManager* CheckpointsManager;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void Increment(ACheckPoint* PassedCheckPoint);
		
};
