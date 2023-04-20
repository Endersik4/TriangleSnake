// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "SnakePawn.h"
#include "TailSnake.h"
#include "PointsCounter.h"


// Sets default values
AApple::AApple()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AApple::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();

	RandomLocationSpawn();

	GetWorldTimerManager().SetTimer(Timer, this, &AApple::SetPointsCounter, 0.1f);
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AApple::RandomLocationSpawn()
{
	int32 x = FMath::Floor(FMath::SRand() * 8) + 1;
	int32 y = FMath::Floor(FMath::SRand() * 16) + 1;
	x = 150 + (x * 100);
	y = 250 + (y * 100);
	FVector Location = FVector(x, y, 50);
	if (CheckIfAppleCanSpawn(Location))
	{
		SetActorLocation(Location);
	}
	else
	{
		RandomLocationSpawn();
	}
}

void AApple::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Snake")))
	{
		ASnakePawn* SnakePawn = Cast<ASnakePawn>(OtherActor);
		if (SnakePawn)
		{
			SnakePawn->SetHasEatenApple(true);
			SnakePawn->SetAppleActor(this);
		}
	}
}


bool AApple::CheckIfAppleCanSpawn(FVector AppleLocation)
{
	TArray<AActor*>Tails;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATailSnake::StaticClass(), Tails);
	for (AActor* TailA : Tails)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s LOCATION = %s"), *TailA->GetActorNameOrLabel(), *TailA->GetActorLocation().ToString());
		if (TailA->GetActorLocation().Equals(AppleLocation, 50.f))
		{
			//UE_LOG(LogTemp, Error, TEXT("APPLE LOCATION = %s"), *AppleLocation.ToString());
			return false;
		}
	}
	return true;
}

void AApple::SetPointsCounter()
{
	TArray<AActor*>PointsArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APointsCounter::StaticClass(), PointsArray);
	if (PointsArray.Num() > 0) 
	{
		APointsCounter* PointCast = Cast<APointsCounter>(PointsArray[0]);
		if (PointCast)
		{
			PointCast->SetPoints(1);
		}
	}
	
}