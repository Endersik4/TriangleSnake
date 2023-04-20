// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakeController.generated.h"

/**
 * 
 */
UCLASS()
class TRIANGLESNAKE_API ASnakeController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetUpCamera();
	class ACameraActor* Camera;


	
};
