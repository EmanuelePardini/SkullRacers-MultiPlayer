// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Interactables.h"

#include "Character/BallPawn.h"

// Sets default values
AInteractables::AInteractables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(RootComponent);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AInteractables::AInteractables::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this,&AInteractables::AInteractables::OnEndOverlap);
}

// Called when the game starts or when spawned
void AInteractables::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractables::Interact(ABallPawn* InteractingPawn)
{
	IInteractionInterface::Interact();
	IInteractionInterface::Execute_OnBeginInteract(this,InteractingPawn);
}

void AInteractables::EndInteract(ABallPawn* InteractingPawn)
{
	IInteractionInterface::EndInteract();
	IInteractionInterface::Execute_OnEndInteract(this,InteractingPawn);
}

void AInteractables::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABallPawn* InteractingPawn = Cast<ABallPawn>(OtherActor);
	if(InteractingPawn)
	{
		Interact(InteractingPawn);
		InteractingPawns.Add(InteractingPawn);
	}
}

void AInteractables::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (int32 i = 0; i < InteractingPawns.Num(); ++i)
	{
		if (InteractingPawns[i] == OtherActor)
		{
			EndInteract(InteractingPawns[i]);
			InteractingPawns.RemoveAt(i);
			break;
		}
	}
}

