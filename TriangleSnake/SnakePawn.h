// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

UCLASS()
class TRIANGLESNAKE_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void SetHasEatenApple(bool bHas) { bHasEatenApple = bHas; };
	void SetAppleActor(AActor* AppleActor) { Apple = AppleActor; };

private:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* HitComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Components")
		class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere, Category = "Components")
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Components")
		class UChromaticAbberationComponent* ChromaticAbberationComponent;

	UPROPERTY(EditAnywhere, Category = "TailSnake")
		TSubclassOf<class ATailSnake>TailSnakeClass;

	UPROPERTY(EditAnywhere, Category = "Moving")
		float DistanceToMove = 100.f;
	UPROPERTY(EditAnywhere, Category = "Moving")
		float  Tolerance = 1.7f;

	UPROPERTY(EditAnywhere, Category = "CornerTail")
		TSubclassOf<class ACornerTail> CornerTailClass;

	UPROPERTY(EditAnywhere, Category = "particles")
		class UNiagaraSystem* OverTailSystem;
	UPROPERTY(EditAnywhere, Category = "particles")
		class UNiagaraSystem* OverFrameSystem;

	UPROPERTY(EditAnywhere, Category = "GameOver")
		TSubclassOf<AActor> GameOverActor;

	int32 IndexLocation = 1;

	
	bool bShouldRotate = false;
	bool bHasEatenApple;
	bool bShouldTailBeVisible = true;
	bool bStartGame = false;

	void SetSnakeGameMode();

	void UpdateMove(float Delta);
	void SetPawnVariablesIfPossible();
	bool IsPawnInCenterOfSquare();
	
	void StartGame(bool bShouldStart) { bStartGame = bShouldStart; };

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void RotatePawn();
	void AteApple();

	FVector StartLocation;
	FVector MoveLocation;
	FVector DistanceToPass;

	FRotator CornerTailRotation;
	FRotator RotationTurn;

	AActor* Apple;
	class ATailSnake* TailSnake;
	class ATriangleSnakeModeBase* SnakeGameMode;
	class ASnakeController* SnakeController;
	
	void SpawnCornerMesh();

};
