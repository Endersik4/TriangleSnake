// Fill out your copyright notice in the Description page of Project Settings.


#include "ChromaticAbberationComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PostProcessVolume.h"

// Sets default values for this component's properties
UChromaticAbberationComponent::UChromaticAbberationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UChromaticAbberationComponent::BeginPlay()
{
	Super::BeginPlay();

	SetUpPostProcessVolume();

	CopySpeed = Speed;
	
}

// Called every frame
void UChromaticAbberationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CalculatingIntensity(DeltaTime);
}

void UChromaticAbberationComponent::CalculatingIntensity(float Delta)
{
	if (bShouldLerpChromatic && PPV)
	{
		//NowIntensity = FMath::FInterpTo(NowIntensity, EatAppleIntensity, DeltaTime, Speed); //Speed = 30
		//NowIntensity = FMath::InterpEaseIn(NowIntensity, EatAppleIntensity, DeltaTime * Speed, Speed/2); 
		//NowIntensity = FMath::InterpCircularInOut(NowIntensity, EatAppleIntensity, DeltaTime * Speed);
		CurrentIntensity = FMath::InterpCircularIn(CurrentIntensity, TargetIntensity, Delta * Speed); //speed = 50
		if (CurrentIntensity >= 7.9)
		{
			CurrentIntensity = 8.f;
			TargetIntensity = 0.5f;
			Speed /= 2;
		}
		if (CurrentIntensity < 0.6f) bShouldLerpChromatic = false;
		PPV->Settings.SceneFringeIntensity = CurrentIntensity;
	}
}

void UChromaticAbberationComponent::BoostUpChromaticAbberation()
{
	bShouldLerpChromatic = true;
	TargetIntensity = 8.f; 
	CurrentIntensity = 0.6f;
	Speed = CopySpeed;
}

void UChromaticAbberationComponent::SetUpPostProcessVolume()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, APostProcessVolume::StaticClass(), Actors);
	if (Actors[0])
	{
		//wymagane #include "Engine/PostProcessVolume.h"
		PPV = Cast<APostProcessVolume>(Actors[0]); //PostProcessVolume
		PPV->Settings.bOverride_SceneFringeIntensity = true;//Gdy to dopiero bedzie true to wtedy
		//bedzie mozna zmienic dana wartosc w tym przypadku Chromatic Abberation Intensity
	}
}