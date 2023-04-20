// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void ASnakeController::BeginPlay()
{
    SetUpCamera();
}

void ASnakeController::SetUpCamera()
{
	TArray<AActor*>CameraArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraArray);
	if (CameraArray.Num() > 0)
	{
		Camera = Cast<ACameraActor>(CameraArray[0]);
		SetViewTarget(Camera);
	}
}


