// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeSizeOfTail.h"
#include "TailSnake.h"
#include "Components/StaticMeshComponent.h"
#include "CornerTail.h"

// Sets default values for this component's properties
UChangeSizeOfTail::UChangeSizeOfTail()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UChangeSizeOfTail::BeginPlay()
{
	Super::BeginPlay();

	Tail = Cast<ATailSnake>(GetOwner());
	DistanceToMove = Tail->GetDistanceToMove();
	
}


// Called every frame
void UChangeSizeOfTail::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UChangeSizeOfTail::ChangeSizeOfMeshes(UStaticMeshComponent& Meshes, const AActor* TailBefore, 
	bool& bOutShouldChangeMeshSize, bool& bOutShouldChangeBetweenMeshes)
{
	if (Tail == nullptr) return;

	TailOrSnake = TailBefore ? TailBefore : Tail->GetSnakePawn();

	if (TailOrSnake && Size == 1.f && !((-Tail->GetActorForwardVector()).Equals((-TailOrSnake->GetActorForwardVector()), 0.01f))) //KRZYZYK
	{
		Meshes.SetVisibility(false);
		bIsTwoCorners = true;
	}
	else
	{
		if (bIsTwoCorners)
		{
			Meshes.SetVisibility(true);
			bIsTwoCorners = false;
		}

		FVector MeshScale = Meshes.GetRelativeScale3D();
		FVector ForwardVectorMesh = FVector(0, ((DistanceToMove / 100.f) * GetWorld()->GetDeltaSeconds()), 0);

		Size == 1.f ? MeshScale += ForwardVectorMesh : MeshScale -= ForwardVectorMesh;
		bool bCheckWhichMeshSizeChange = Size == 1.f ? Meshes.GetRelativeScale3D().Y < Size : Meshes.GetRelativeScale3D().Y > Size;

		if (bCheckWhichMeshSizeChange)
		{
			Meshes.SetRelativeScale3D(MeshScale);
		}
		else
		{
			Meshes.SetRelativeScale3D(FVector(1, Size, 1));
			bOutShouldChangeMeshSize = false;
			bOutShouldChangeBetweenMeshes = true;
		}
	}
}

UStaticMeshComponent* UChangeSizeOfTail::ChangeBetweenMeshes(UStaticMeshComponent& OutMeshes, UStaticMeshComponent& OutMeshOneTail, UStaticMeshComponent& OutMeshTwoTail, 
	bool& bOutShouldChangeMeshSize, bool& bOutShouldChangeBetweenMeshes)
{
	if (Tail == nullptr) return nullptr;

	if (Tail->GetIndexLocation() != 1)
	{
		if (&OutMeshes == &OutMeshOneTail)
		{
			OutMeshOneTail.SetVisibility(false);
			OutMeshOneTail.SetRelativeScale3D(FVector(1, 1, 1));

			OutMeshTwoTail.SetVisibility(true);

			bOutShouldChangeMeshSize = true;
			Size = 1.f;
			bOutShouldChangeBetweenMeshes = false;

			return &OutMeshTwoTail;
		}
		else
		{
			OutMeshTwoTail.SetVisibility(false);
			OutMeshTwoTail.SetRelativeScale3D(FVector(1, 0.3f, 1));

			OutMeshOneTail.SetVisibility(true);

			bOutShouldChangeMeshSize = false;
			Size = 0.3f;
			bOutShouldChangeBetweenMeshes = false;

			return &OutMeshOneTail;
		}
	}
	else
	{
		CurrentCorner->SetActorHiddenInGame(true);
		CurrentCorner->SetActorLocation(FVector(0, 0, -200));
		CurrentCorner->GetRootComponent()->SetActive(false);

		OutMeshOneTail.SetRelativeScale3D(FVector(1, 1, 1));
		bOutShouldChangeBetweenMeshes = false;
		return &OutMeshOneTail;
	}
	
}