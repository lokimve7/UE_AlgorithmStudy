// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeBlock.generated.h"

UCLASS()
class ALGORITHMSTUDY_API ACubeBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Cost 구하는 함수
	void SetCost(class ACubeBlock* s, class ACubeBlock* g);

	// OutLine 색 바꾸는 함수
	void SetColor(FLinearColor color);

	void SetInit();

	//OutLine Widget
	UPROPERTY()
	class UBorder* outLine;
	//sCost Widget
	UPROPERTY()
	class UTextBlock* sCost;
	//sCost Value
	float sCostValue;
	//gCost Widget
	UPROPERTY()
	class UTextBlock* gCost;
	//tCost Widget
	UPROPERTY()
	class UTextBlock* tCost;
	float tCostValue;

	UPROPERTY()
	class ACubeBlock* parentCube;
};
