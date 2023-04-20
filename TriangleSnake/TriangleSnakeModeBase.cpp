// Fill out your copyright notice in the Description page of Project Settings.


#include "TriangleSnakeModeBase.h"
#include "Apple.h"

void ATriangleSnakeModeBase::BeginPlay()
{
	SpawnNewApple();
}

void ATriangleSnakeModeBase::SpawnNewApple()
{
	if (AppleSpawn)
	{
		GetWorld()->SpawnActor<AApple>(AppleSpawn, FVector(0, 0, -100), FRotator(0, 0, 0));
	}
}


