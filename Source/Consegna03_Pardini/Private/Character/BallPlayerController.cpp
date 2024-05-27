// Fill out your copyright notice in the Description page of Project Settings.


#include "Consegna03_Pardini/Public/Character/BallPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/PlayerInputData.h"

void ABallPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Add Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}
	
	BallPawn = Cast<ABallPawn>(GetPawn());
}

void ABallPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABallPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputData->Move, ETriggerEvent::Triggered, this, &ABallPlayerController::Move);
		EnhancedInputComponent->BindAction(InputData->Look, ETriggerEvent::Triggered, this, &ABallPlayerController::Look);
		EnhancedInputComponent->BindAction(InputData->Jump, ETriggerEvent::Triggered, this, &ABallPlayerController::Jump);
		EnhancedInputComponent->BindAction(InputData->Boost, ETriggerEvent::Started, this, &ABallPlayerController::Boost);
	}
}

void ABallPlayerController::Move(const FInputActionValue& Value)
{
	if(BallPawn) BallPawn->Move(Value);
}

void ABallPlayerController::Look(const FInputActionValue& Value)
{
	if(BallPawn) BallPawn->Look(Value);
}

void ABallPlayerController::Jump(const FInputActionValue& Value)
{
	if(BallPawn) BallPawn->DoJump(Value);
}

void ABallPlayerController::Boost(const FInputActionValue& Value)
{
	if(BallPawn) BallPawn->Boost(Value);
}

