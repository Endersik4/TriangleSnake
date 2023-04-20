// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsCounter.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APointsCounter::APointsCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	PointsText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PointsText"));
	PointsText->SetupAttachment(RootComponent);
	PointsText->SetText(FText::FromString(TEXT("0")));

	HighScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HighScoreText"));
	HighScoreText->SetupAttachment(RootComponent);
	HighScoreText->SetText(FText::FromString(TEXT("0")));
}

// Called when the game starts or when spawned
void APointsCounter::BeginPlay()
{
	Super::BeginPlay();
	LoadGame();
	FString ScoreString = FString::FromInt(HighScore);
	HighScoreText->SetText(FText::FromString(ScoreString));
}

void APointsCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterpScale(WhichText, DeltaTime);
}

void APointsCounter::SetPoints(int32 Point)
{
	Points += Point;
	FString PointsString = FString::FromInt(Points);
	PointsText->SetText(FText::FromString(PointsString));

	WhichText = PointsText;
	bShouldInterpScale = true;
}

void APointsCounter::SetHighScore(int32 High)
{
	HighScore = High;
	FString ScoreString = FString::FromInt(HighScore);
	HighScoreText->SetText(FText::FromString(ScoreString));

	WhichText = HighScoreText;
	bShouldInterpScale = true;

	SaveGame();
}


//Zapisywanie Gry, najpierw trzeba stworzyc klase w C++ SaveGame (jest w All Classes), pozniej wpisac tam dane
//ktore chcemy zapisac
void APointsCounter::SaveGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->HighScore = HighScore;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);//Zapisuje do slotu
}

void APointsCounter::LoadGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	if (SaveGameInstance) HighScore = SaveGameInstance->HighScore;
}

void APointsCounter::InterpScale(UTextRenderComponent* Text, float Delta)
{
	if (Text == nullptr || bShouldInterpScale == false) return;
	CurrentScale = FMath::InterpCircularIn(Text->GetComponentScale().X, TargetScale, Delta * Speed);
	FVector TextScale = FVector(CurrentScale, CurrentScale, CurrentScale);
	Text->SetWorldScale3D(TextScale);
	if (CurrentScale >= 0.9)
	{
		CurrentScale = 1.f;
		TargetScale = 0.4f;
	}
	if (CurrentScale < 0.5f)
	{
		bShouldInterpScale = false;
		CurrentScale = 0.5f;
		TargetScale = 2.f;
	}
}

