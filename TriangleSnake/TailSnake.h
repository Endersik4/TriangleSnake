// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TailSnake.generated.h"

class UStaticMeshComponent;

UCLASS()
class TRIANGLESNAKE_API ATailSnake : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATailSnake();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 GetIndexLocation() const { return IndexLocation; };
	void SetIndexLocation(int32 Ind);

	float GetDistanceToMove() const { return DistanceToMove; };
	AActor* GetSnakePawn() const { return SnakePawn; };

	void SetShouldUpdateMove(bool bShould);
	void SetGameOver(bool bShould) { bShouldUpdateMove = bShould; }
	void SetShouldBeVisible(bool bShould) { bShouldBeVisible = bShould; }

	void SetShouldChangeMeshSize(bool bShould) { bShouldChangeMeshSize = bShould; }

	void SetShouldGoToSnake(bool bShould) { bShouldGoToSnake = bShould; }

	class UChangeSizeOfTail* GetChangeSizeComponent() const { return ChangeSizeComponent; };


private:
	UPROPERTY(EditAnywhere, Category = "Components")
		class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* MeshTwo;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UStaticMesh* EndTailMesh;

	UPROPERTY(EditAnywhere, Category = "Change")
		class UChangeSizeOfTail* ChangeSizeComponent;

	UPROPERTY(EditAnywhere, Category = "Moving")
		float DistanceToMove = 100.f;
	UPROPERTY(EditAnywhere, Category = "Moving")
		float  Tolerance = 1.7f;

	int32 IndexLocation = 1; //Unique Number for Tail
	int32 WaitOneTick = 0;

	bool bShouldGoToSnake = false;
	bool bShouldUpdateMove;
	
	//Setting up 
	
	void SearchForAndSetTailToFollow();
	void SetSnakePawn();
	void SetLocationAndRotationForTail();
	void ReplaceTailToFollowSnake();

	//Move methods
	void UpdateMove(float Delta);
	void CheckIfTailShouldUpdateDistancePass();
	void ProperTailRotation();

	UStaticMeshComponent* WhichMesh = Mesh;

	FVector StartLocation;
	FVector MoveLocation;
	FVector DistanceToPass;

	AActor* SnakePawn = nullptr;
	ATailSnake* TailAhead = nullptr;
	AActor* TailBehind;

	//Bools for Corner Tail to work properly
	bool bShouldChangeBetweenMeshes = false;
	bool bShouldChangeMeshSize = false;
	bool bJustSpawned = true;
	bool bShouldBeVisible = true;
	//Method for Change Size of Mesh
	void ChangeSizeOfMesh();
	void SetStaticMesh();

	
};
