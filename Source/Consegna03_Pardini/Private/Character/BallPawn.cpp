// Fill out your copyright notice in the Description page of Project Settings.


#include "Consegna03_Pardini/Public/Character/BallPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CheckpointComponent.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABallPawn::ABallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BallCollider = CreateDefaultSubobject<USphereComponent>("BallCollider");
	BallCollider->SetupAttachment(RootComponent);

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	BallMesh->SetupAttachment(BallCollider);

	//Camera Settings
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(BallCollider);
	CameraBoom->bUsePawnControlRotation = true;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCamera->SetupAttachment(CameraBoom);
	ThirdPersonCamera->SetActive(true);
	ThirdPersonCamera->bUsePawnControlRotation = false;

	//Components
	ScoreComponent = CreateDefaultSubobject<UScoreComponent>("ScoreComponent");
	CheckpointComponent = CreateDefaultSubobject<UCheckpointComponent>("CheckpointComponent");
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ManageTimers(DeltaTime);
}

void ABallPawn::ManageTimers(float DeltaTime)
{
	BoostRechargeTimer += DeltaTime;

	if(BoostRechargeTimer >= BoostRechargeDelay) bCanBoost = true;

	if(bIsBoosting)
	{
		BoostTimer += DeltaTime;
		if(BoostTimer >= BoostDelay) EndBoost();
	}
}

void ABallPawn::Move(const FInputActionValue& Value)
{
	// Get the input value for movement
	FVector2D MovementValue = Value.Get<FVector2D>();

	// Normalize the movement vector to ensure constant movement speed regardless of direction
	MovementValue.Normalize();

	// Get the rotation of the camera boom
	FRotator CameraRotation = ThirdPersonCamera->GetComponentRotation();

	// Convert rotation to a forward vector
	FVector ForwardDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);
	// Convert rotation to a right vector
	FVector RightDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

	// Calculate the direction to move in using the input vectors and the camera's rotation
	FVector MoveDirection = ForwardDirection * MovementValue.Y + RightDirection * MovementValue.X;

	// Normalize the combined movement vector to ensure constant movement speed regardless of direction
	MoveDirection.Normalize();

	// Apply the force to the pawn's physics simulation component in the desired direction
	BallCollider->AddForce(MoveDirection * MoveForce * 100.f);
	
	if(!HasAuthority()) Server_Move(MoveDirection);
}

bool ABallPawn::Server_Move_Validate(FVector Value)
{
	return true;
}

void ABallPawn::Server_Move_Implementation(FVector Value)
{
	BallCollider->AddForce(Value * MoveForce * 100.f);
}


void ABallPawn::Look(const FInputActionValue& Value)
{
	FVector2d LookValue = Value.Get<FVector2d>();
	
	// Adds input to control the rotation
	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}

void ABallPawn::DoJump(const FInputActionValue& Value)
{
	if(!IsPawnGrounded()) return;
	
	// Apply the jump force in the vertical direction
	FVector JumpDirection = FVector(0, 0, JumpForce * 100.f);
	BallCollider->AddForce(JumpDirection);
	if(!HasAuthority()) Server_Jump(JumpDirection);
	PlayDoJump();
}

bool ABallPawn::Server_Jump_Validate(FVector JumpDirection)
{
	return true;
}

void ABallPawn::Server_Jump_Implementation(FVector JumpDirection)
{
	BallCollider->AddForce(JumpDirection);
}

void ABallPawn::Boost_Implementation(const FInputActionValue& Value)
{
	if(!bCanBoost) return;
	
	MoveForce *= 2;
	bIsBoosting = true;
	bCanBoost = false;
	PlayBoost();
}

void ABallPawn::EndBoost_Implementation()
{
	MoveForce /= 2;
	bIsBoosting = false;
	bCanBoost = false;
	BoostRechargeTimer = 0.f;
	BoostTimer = 0.f;
}

void ABallPawn::Die_Implementation()
{
	FVector LastCheckPoint;
	if(CheckpointComponent && !CheckpointComponent->PassedCheckPoints.IsEmpty() && CheckpointComponent->PassedCheckPoints.Num() > 0 )
	{
		LastCheckPoint = CheckpointComponent->PassedCheckPoints.Last()->GetActorLocation();
	}
	else
	{
		LastCheckPoint = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass())->GetActorLocation();
	}
	
	SetActorLocation(LastCheckPoint);
	PlayDie();
}

bool ABallPawn::IsPawnGrounded()
{
	// Get the position of the collision sphere
	FVector SphereLocation = BallCollider->GetComponentLocation();

	// Get the downward direction
	FVector DownwardDirection = FVector(0, 0, -1);

	// Length of the raycast
	float RaycastLength = 100.0f; // Adjust this length based on the pawn's dimensions

	// Set up parameters for the raycast
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore the pawn itself to avoid collisions with itself

	// Perform the raycast
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, SphereLocation, SphereLocation + DownwardDirection * RaycastLength, ECC_WorldStatic, Params);

	// Return true if there is a collision
	return bHit;
}

//TODO: Use chaos on die when hit a wall
