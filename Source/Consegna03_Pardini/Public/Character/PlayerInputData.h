// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInputData.generated.h"

/**
 * 
 */
UCLASS()
class CONSEGNA03_PARDINI_API UPlayerInputData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	class UInputAction* Move;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* Look;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* Jump;
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	UInputAction* Boost;
	
};
