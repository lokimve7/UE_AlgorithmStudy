// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuzzleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMSTUDY_API UPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void InitCard();
	void SelectCard(FVector2D mousePos);
	void FindNearCard(int32 idx);

public:
	UPROPERTY(EditAnywhere)
	TArray<class UBorder*> cardWidgets;

	UPROPERTY(EditAnywhere)
	TArray<int32> cardValues;	

	// 카드크기
	float cardSize = 120;
	// 카드가로갯수
	int32 hCount = 3;
	// 카드가로세로갯수
	int32 vCount = 3;

	// 첫번째 카드의 위치(보정을 위해)
	float offsetX;
	float offsetY;
};
