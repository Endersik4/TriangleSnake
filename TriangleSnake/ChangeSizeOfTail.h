// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ChangeSizeOfTail.generated.h"

/**
 * ChangeSizeOfTail is used to change size of Tail when Tail collide with
 * Corner Tail 
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIANGLESNAKE_API UChangeSizeOfTail : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChangeSizeOfTail();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeSizeOfMeshes(UStaticMeshComponent& Meshes, const AActor* TailBefore,
		bool& bOutShouldChangeMeshSize, bool& bOutShouldChangeBetweenMeshes);
	
	UStaticMeshComponent* ChangeBetweenMeshes(UStaticMeshComponent& OutMeshes, UStaticMeshComponent& OutMeshOneTail, 
		UStaticMeshComponent& OutMeshTwoTail, bool& bOutShouldChangeMeshSize, bool& bOutShouldChangeBetweenMeshes);

	void SetCurrentCorner(AActor* Corner) { CurrentCorner = Corner; };
	
private:
	class ATailSnake* Tail;
	const AActor* TailOrSnake;
	AActor* CurrentCorner;

	bool bIsTwoCorners = false;
	float Size = 0.3f;
	float DistanceToMove;	
		
};
