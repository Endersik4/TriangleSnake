// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainMenu::AMainMenu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	StartGameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("StartGameText"));
	StartGameText->SetupAttachment(RootComponent);
	BoxStart = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxStart"));
	BoxStart->SetupAttachment(StartGameText);

	QuitGameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("QuitGameText"));
	QuitGameText->SetupAttachment(RootComponent);
	BoxQuit = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxQuit"));
	BoxQuit->SetupAttachment(QuitGameText);

}

// Called when the game starts or when spawned
void AMainMenu::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainMenu::StartGameOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("ASDd"));
	FName MapName = "Main_map";
	UGameplayStatics::OpenLevel(GetWorld(), MapName);
}

void AMainMenu::QuitOnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Background, true);
}


