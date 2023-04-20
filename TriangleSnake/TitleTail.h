// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TitleTail.generated.h"

UCLASS()
class TRIANGLESNAKE_API ATitleTail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATitleTail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

};
