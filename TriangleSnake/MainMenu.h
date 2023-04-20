// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenu.generated.h"

class UTextRenderComponent;
class UBoxComponent;

UCLASS()
class TRIANGLESNAKE_API AMainMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Components", BlueprintReadWrite)
		UTextRenderComponent* StartGameText;
	UPROPERTY(EditDefaultsOnly, Category = "Components", BlueprintReadWrite)
		UTextRenderComponent* QuitGameText;

private:
	UFUNCTION(BlueprintCallable)
		void StartGameOnClicked();
	UFUNCTION(BlueprintCallable)
		void QuitOnClicked();
	//UFUNCTION()
	//	void TextOnEndMouseOver(UPrimitiveComponent* TouchedComponent);

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Boxes")
		UBoxComponent* BoxStart;
	UPROPERTY(EditDefaultsOnly, Category = "Boxes")
		UBoxComponent* BoxQuit;


};
