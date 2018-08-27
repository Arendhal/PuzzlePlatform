// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Checking if we are the server
	if (HasAuthority()) { //If yes move the platform
		FVector location = GetActorLocation();
		location += FVector(PlatformSpeed * DeltaTime, 0, 0);
		SetActorLocation(location); //Set the new position of the platform
	}
	
}
