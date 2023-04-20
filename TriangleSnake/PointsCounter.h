// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointsCounter.generated.h"

UCLASS()
class TRIANGLESNAKE_API APointsCounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointsCounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetPoints(int32 Point);
	void SetHighScore(int32 High);
	
	int32 GetHighScore() const { return HighScore; }
	int32 GetPoints() const { return Points; }

private:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		class UTextRenderComponent* PointsText;

	UPROPERTY(EditAnywhere)
		class UTextRenderComponent* HighScoreText;

	UPROPERTY(EditAnywhere, Category = "Interp Scale")
		double TargetScale = 2.f;
	UPROPERTY(EditAnywhere, Category = "Interp Scale")
		double Speed = 10.f;

	int32 Points = -1;
	int32 HighScore = 0;

	void SaveGame();
	void LoadGame();

	void InterpScale(class UTextRenderComponent* Text, float Delta);
	bool bShouldInterpScale = false;
	double CurrentScale = 1;
	class UTextRenderComponent* WhichText;

};
