// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleTail.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ChangeSizeOfTail.h"

// Sets default values
ATitleTail::ATitleTail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ATitleTail::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATitleTail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
