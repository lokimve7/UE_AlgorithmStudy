// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PuzzlePawn.generated.h"

UCLASS()
class ALGORITHMSTUDY_API APuzzlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APuzzlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPuzzleWidget> puzzleWidgetClass;

	UPROPERTY(EditAnywhere)
	class UPuzzleWidget* puzzleWidget;

	void InputRMouse();
	void InputRMouseUp();

	
};
