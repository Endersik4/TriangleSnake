// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TriangleSnakeModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TRIANGLESNAKE_API ATriangleSnakeModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SpawnNewApple();

private:
	UPROPERTY(EditAnywhere, Category = "Level Settings")
		TSubclassOf<class AApple>AppleSpawn;
	
};
