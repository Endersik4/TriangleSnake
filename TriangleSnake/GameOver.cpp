// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

#include "PointsCounter.h"

// Sets default values
AGameOver::AGameOver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	RootComponent = Plane;
	
}

// Called when the game starts or when spawned
void AGameOver::BeginPlay()
{
	Super::BeginPlay();
	SetPointCounter();
}

// Called every frame
void AGameOver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameOver::BackToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuMap"));
}

void AGameOver::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Main_map"));
}
void AGameOver::SetPointCounter()
{
	TArray<AActor*>PointsArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APointsCounter::StaticClass(), PointsArray);
	if (PointsArray.Num() > 0)
	{
		APointsCounter* PointCast = Cast<APointsCounter>(PointsArray[0]);
		if (PointCast->GetHighScore() != 0)
		{
			if (PointCast->GetPoints() > PointCast->GetHighScore())
			{
				PointCast->SetHighScore(PointCast->GetPoints());
			}
		}
		else PointCast->SetHighScore(PointCast->GetPoints());
	}
}


