// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ChromaticAbberationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIANGLESNAKE_API UChromaticAbberationComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChromaticAbberationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void BoostUpChromaticAbberation();

private:
	UPROPERTY(EditAnywhere, Category = "Interpto")
		float Speed = 10.f;
	UPROPERTY(EditAnywhere, Category = "Interpto")
		float TargetIntensity = 10.f;	 //of chromatic abberation in Post process voluem

	void SetUpPostProcessVolume();
	class APostProcessVolume* PPV;

	void CalculatingIntensity(float Delta);
	bool bShouldLerpChromatic = false;
	float CurrentIntensity = 0.6f;
	float CopySpeed;
};
