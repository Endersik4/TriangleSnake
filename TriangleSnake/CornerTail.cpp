// Fill out your copyright notice in the Description page of Project Settings.


#include "CornerTail.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TailSnake.h"
#include "ChangeSizeOfTail.h"

// Sets default values
ACornerTail::ACornerTail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACornerTail::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ACornerTail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACornerTail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACornerTail::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Tail"))
	{
		ATailSnake* TailSnake = Cast<ATailSnake>(OtherActor);
		if (TailSnake)
		{
			if (TailSnake->GetIndexLocation() == 1)
			{
				TailSnake->GetChangeSizeComponent()->SetCurrentCorner(this);
			}
			TailSnake->SetShouldChangeMeshSize(true);
		}
	}
}
