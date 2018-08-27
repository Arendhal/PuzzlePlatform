// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() 
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true); //Set the replication for this actor to true
		SetReplicateMovement(true); //Enables the replication of this actors's movement
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	//Checking if we are the server
	if (HasAuthority()) { //If yes move the platform
		FVector Location = GetActorLocation();

		float TravelLenght = (GlobalTargetLocation - GlobalStartLocation).Size();
		float Travelled = (Location - GlobalStartLocation).Size();

		if (Travelled > TravelLenght)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GetActorLocation();
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += PlatformSpeed * DeltaTime * Direction;
		SetActorLocation(Location); //Set the new position of the platform
	}
}
