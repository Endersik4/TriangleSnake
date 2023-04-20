// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "TriangleSnakeModeBase.h"
#include "TailSnake.h"
#include "CornerTail.h"
#include "SnakeController.h"
#include "ChromaticAbberationComponent.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ChromaticAbberationComponent = CreateDefaultSubobject<UChromaticAbberationComponent>(TEXT("ChromaticAbberationComponent"));
	ChromaticAbberationComponent->SetupAttachment(RootComponent);

	BoxComp->OnComponentHit.AddDynamic(this, &ASnakePawn::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();

	SnakeController = Cast<ASnakeController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	SetSnakeGameMode();

	StartLocation = GetActorLocation();
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartGame)
	{
		UpdateMove(DeltaTime);

		if (IsPawnInCenterOfSquare())
		{
			SetPawnVariablesIfPossible();
		}
	}
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &ASnakePawn::MoveUp);
	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &ASnakePawn::MoveDown);
	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &ASnakePawn::MoveLeft);
	PlayerInputComponent->BindAction("Right", IE_Pressed, this, &ASnakePawn::MoveRight);

}

void ASnakePawn::UpdateMove(float Delta)
{
	MoveLocation = GetActorLocation() + -GetActorForwardVector() * (DistanceToMove * Delta);
	SetActorLocation(MoveLocation);
}

bool ASnakePawn::IsPawnInCenterOfSquare()
{
	DistanceToPass = StartLocation + -GetActorForwardVector() * 100.f;
	return DistanceToPass.Equals(GetActorLocation(), Tolerance);
}

void ASnakePawn::SetPawnVariablesIfPossible()
{
	SetActorLocation(DistanceToPass);

	StartLocation = GetActorLocation();
	DistanceToPass = StartLocation + -GetActorForwardVector() * 100.f;

	bShouldTailBeVisible = true;

	if (TailSnake)
	{
		TailSnake->SetShouldUpdateMove(false);
		TailSnake->SetActorHiddenInGame(false);
	}

	RotatePawn();
	AteApple();
}

void ASnakePawn::RotatePawn()
{
	
	if (bShouldRotate)
	{
		SetActorRotation(RotationTurn);

		bShouldTailBeVisible = false;
		bShouldRotate = false;

		SpawnCornerMesh();
	}
}

void ASnakePawn::SpawnCornerMesh()
{
	if (CornerTailClass && TailSnake)
	{
		GetWorld()->SpawnActor<ACornerTail>(CornerTailClass, GetActorLocation(), CornerTailRotation);
	}
}

void ASnakePawn::AteApple()
{
	if (bHasEatenApple)
	{
		if (Apple == nullptr || SnakeGameMode == nullptr) return;

		ChromaticAbberationComponent->BoostUpChromaticAbberation();
		Apple->Destroy();
		SnakeGameMode->SpawnNewApple();

		if (TailSnakeClass)
		{
			TailSnake = GetWorld()->SpawnActor<ATailSnake>(TailSnakeClass, (GetActorLocation() + FVector(0,0,200)), GetActorRotation());
			TailSnake->SetIndexLocation(IndexLocation);
			IndexLocation++;
			TailSnake->SetShouldUpdateMove(true);
			TailSnake->SetShouldGoToSnake(true);
		}

		if (bShouldTailBeVisible == false)
		{
			TailSnake->SetShouldBeVisible(false);
		}
		bHasEatenApple = false;
	}
}

void ASnakePawn::OnBoxBeginOverlap(UPrimitiveComponent* HitComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->ActorHasTag(TEXT("Apple")))
	{
		if (OtherActor == TailSnake || OtherActor->ActorHasTag("Corner")) return;

		FVector LocNiagara = GetActorLocation() * (-GetActorForwardVector() * 17.f);
		UNiagaraSystem* WhichSystem = (OtherActor->ActorHasTag("Tail")) ? OverTailSystem : OverFrameSystem;
		if (WhichSystem) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WhichSystem, GetActorLocation());
		
		bStartGame = false;
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (TailSnake)
		{
			TailSnake->SetGameOver(true);
			TailSnake->SetShouldUpdateMove(true);
		}

		if (GameOverActor)
		{
			GetWorld()->SpawnActor<AActor>(GameOverActor, FVector(723, 1026, 226), FRotator(0, 90, 0));
		}
	}
}

void ASnakePawn::MoveUp()
{
	if (bStartGame == false) StartGame(true);

	if (!((-GetActorForwardVector()).X > 0.5f) && !((-GetActorForwardVector()).X < -0.5f))
	{
		bShouldRotate = true;
		RotationTurn = FRotator(0, 180, 0);

		if ((-GetActorForwardVector()).Y < -0.5f) CornerTailRotation = FRotator(0, 90, 0);
		else CornerTailRotation = FRotator(0, 0, 0);
	}
	//ForwardVec = +X
}

void ASnakePawn::MoveDown()
{
	if (bStartGame == false) StartGame(true);

	if (!((-GetActorForwardVector()).X < -0.5f) && !((-GetActorForwardVector()).X > 0.5f))
	{
		bShouldRotate = true;
		RotationTurn = FRotator(0, 0, 0);

		if ((-GetActorForwardVector()).Y < -0.5f) CornerTailRotation = FRotator(0, 180, 0);
		else CornerTailRotation = FRotator(0, -90, 0);
	}
	//ForwardVec = -X
}

void ASnakePawn::MoveLeft()
{
	if (bStartGame == false) StartGame(true);

	if (!((-GetActorForwardVector()).Y < -0.5f) && !((-GetActorForwardVector()).Y > 0.5f))
	{
		bShouldRotate = true;
		RotationTurn = FRotator(0, 90, 0);

		if ((-GetActorForwardVector()).X < -0.5f) CornerTailRotation = FRotator(0, 0, 0);
		else CornerTailRotation = FRotator(0, -90, 0);
	}
	//ForwardVec = -Y
}

void ASnakePawn::MoveRight()
{
	if (bStartGame == false) StartGame(true);

	if (!((-GetActorForwardVector()).Y > 0.5f) && !((-GetActorForwardVector()).Y < -0.5f))
	{
		bShouldRotate = true;
		RotationTurn = FRotator(0, -90, 0);

		if ((-GetActorForwardVector()).X < -0.5f) CornerTailRotation = FRotator(0, 90, 0);
		else CornerTailRotation = FRotator(0, 180, 0);
	}
	//ForwardVec = +Y
}

void ASnakePawn::SetSnakeGameMode()
{
	TArray<AActor*> SnakeGameModeArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriangleSnakeModeBase::StaticClass(), SnakeGameModeArray);
	if (SnakeGameModeArray[0])
	{
		SnakeGameMode = Cast<ATriangleSnakeModeBase>(SnakeGameModeArray[0]);
	}
}