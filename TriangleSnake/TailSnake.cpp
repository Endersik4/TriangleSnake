// Fill out your copyright notice in the Description page of Project Settings.


#include "TailSnake.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SnakePawn.h"
#include "ChangeSizeOfTail.h"

// Sets default values
ATailSnake::ATailSnake()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MeshTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshTwo"));
	MeshTwo->SetupAttachment(RootComponent);
	MeshTwo->SetVisibility(false);

	ChangeSizeComponent = CreateDefaultSubobject<UChangeSizeOfTail>(TEXT("ChangeSizeOfTail"));
	ChangeSizeComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATailSnake::BeginPlay()
{
	Super::BeginPlay();

	WhichMesh = Mesh;

	/*SetIndexLocation();
	SetSnakePawn();
	SearchForAndSetTailToFollow();

	SetLocationAndRotationForTail();
	*/
	//SetActorHiddenInGame(true);
}

// Called every frame
void ATailSnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldUpdateMove == false)
	{
		if (WaitOneTick == 1)
		{
			UpdateMove(DeltaTime);
			ChangeSizeOfMesh();
			CheckIfTailShouldUpdateDistancePass();
		}
		else WaitOneTick = 1;
	}
}

void ATailSnake::UpdateMove(float Delta)
{
	MoveLocation = GetActorLocation() + -GetActorForwardVector() * (DistanceToMove * Delta);
	SetActorLocation(MoveLocation);
}

void ATailSnake::CheckIfTailShouldUpdateDistancePass()
{
	DistanceToPass = StartLocation + -GetActorForwardVector() * 100.f;
	if (DistanceToPass.Equals(GetActorLocation(), Tolerance))
	{
		SetActorLocation(DistanceToPass);
		StartLocation = GetActorLocation();
		ProperTailRotation();
	}
}

void ATailSnake::ProperTailRotation()
{
	if (bShouldChangeBetweenMeshes)
	{
		WhichMesh = ChangeSizeComponent->ChangeBetweenMeshes(*WhichMesh, *Mesh, *MeshTwo, bShouldChangeMeshSize, bShouldChangeBetweenMeshes);
	}

	if (bShouldGoToSnake && SnakePawn)
	{
		SetActorRotation(SnakePawn->GetActorRotation());
	}
	else if (TailBehind)
	{
		SetActorRotation(TailBehind->GetActorRotation());
	}
}

void ATailSnake::ChangeSizeOfMesh()
{
	if (bShouldBeVisible == true)
	{
		SetActorHiddenInGame(false);
	}

	if (bShouldChangeMeshSize)
	{
		if (bJustSpawned == true && !IsHidden())
		{
			bShouldChangeBetweenMeshes = true;
			WhichMesh = ChangeSizeComponent->ChangeBetweenMeshes(*WhichMesh, *Mesh, *MeshTwo, bShouldChangeMeshSize, bShouldChangeBetweenMeshes);
		}
		ChangeSizeComponent->ChangeSizeOfMeshes(*WhichMesh, TailBehind, bShouldChangeMeshSize, bShouldChangeBetweenMeshes);
	}
	bJustSpawned = false;
}

void ATailSnake::SetIndexLocation(int32 Ind)
{
	IndexLocation = Ind;
	if (IndexLocation == 1)
	{
		SetStaticMesh();
	}
	SetSnakePawn();
	SearchForAndSetTailToFollow();

	SetLocationAndRotationForTail();
}

void ATailSnake::SetSnakePawn()
{
	TArray<AActor*> SnakeArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASnakePawn::StaticClass(), SnakeArray);
	if (SnakeArray[0])
	{
		SnakePawn = SnakeArray[0];
	}
}

void ATailSnake::SearchForAndSetTailToFollow()
{
	TArray<AActor*> TailsArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATailSnake::StaticClass(), TailsArray);
	for (AActor* Tail : TailsArray)
	{
		ATailSnake* TailCast = Cast<ATailSnake>(Tail);
		if (TailCast)
		{
			if (TailCast->GetIndexLocation() == IndexLocation - 1)
			{
				TailAhead = TailCast;
				break;
			}
		}
	}

}

void ATailSnake::SetLocationAndRotationForTail()
{
	ReplaceTailToFollowSnake();
	if (SnakePawn)
	{
		bShouldGoToSnake = true;
		FVector OffSet = SnakePawn->GetActorLocation() + GetActorForwardVector() * 101.f;
		StartLocation = OffSet;
		SetActorLocation(OffSet);
		SetActorRotation(SnakePawn->GetActorRotation());
	}
}

void ATailSnake::ReplaceTailToFollowSnake()
{
	if (TailAhead)
	{
		TailAhead->SetShouldUpdateMove(true);
		TailAhead->bShouldGoToSnake = false;
		TailAhead->TailBehind = this;
	}
}

void ATailSnake::SetShouldUpdateMove(bool bShould)
{
	if (!bShouldGoToSnake)
	{
		bShouldUpdateMove = bShould;
	}
	if (TailAhead)
	{
		TailAhead->SetShouldUpdateMove(bShould);
	}
}

void ATailSnake::SetStaticMesh()
{
	if (EndTailMesh)
	{
		Mesh->SetStaticMesh(EndTailMesh);
	}
}
