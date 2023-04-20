// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOver.generated.h"

UCLASS()
class TRIANGLESNAKE_API AGameOver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable)
		void BackToMenu();
	UFUNCTION(BlueprintCallable)
		void RestartGame();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* Plane;

	void SetPointCounter();
};
