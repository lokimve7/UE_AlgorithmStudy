// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWidget.h"
#include <Components/Border.h>
#include <Components/CanvasPanelSlot.h>

void UPuzzleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 카드 Border 가져오자
	for (int32 i = 0; i < 9; i++)
	{
		FString widgetName = FString::Printf(TEXT("Card_%d"), i);
		UWidget* widget = GetWidgetFromName(*widgetName);
		UBorder* card = Cast<UBorder>(widget);
		cardWidgets.Add(card);

		// 만약에 i 가 0 이라면(첫번째 카드라면)
		if (i == 0)
		{
			// 카드의 위치값을 저장
			UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(card->Slot);
			offsetX = slot->GetPosition().X;
			offsetY = slot->GetPosition().Y;
		}
	}	

	// 카드 초기화
	InitCard();
}

void UPuzzleWidget::InitCard()
{
	// 카드의 값을 초기화
	cardValues.Empty();

	// 랜덤으로 카드의 색상을 바꾸자 (파란색, 노란색)
	for (int32 i = 0; i < cardWidgets.Num(); i++)
	{
		// 랜덤한 값을 뽑자 (0, 1)
		int32 rand = FMath::RandRange(0, 1);

		// 카드의 값을 설정
		cardValues.Add(rand);

		// 0 번이면 파란색, 1 번이면 노란색
		if (rand == 0)
		{
			cardWidgets[i]->SetBrushColor(FLinearColor::Blue);
		}
		else
		{
			cardWidgets[i]->SetBrushColor(FLinearColor::Yellow);
		}
	}
}

void UPuzzleWidget::SelectCard(FVector2D mousePos)
{
	// (x / 카드크기) + (y / 카드크기) * 카드가로갯수 = 선택된 카드 Index
	int32 hIndex = (int32)((mousePos.X - offsetX) / cardSize);
	int32 vIndex = (int32)((mousePos.Y - offsetY) / cardSize);
	int32 selectCardIdx = hIndex + vIndex * hCount;

	UE_LOG(LogTemp, Warning, TEXT("select card = %d"), selectCardIdx);

	// 선택한 카드는 빨간색
	cardWidgets[selectCardIdx]->SetBrushColor(FLinearColor::Red);

	// 근처 카드를 찾자 (상, 하, 좌, 우)
	FindNearCard(selectCardIdx);
}

void UPuzzleWidget::FindNearCard(int32 idx)
{
	int32 n;

	// 상
	// if (idx > hCount - 1)
	if (idx / hCount > 0)
	{
		n = idx - hCount;
		UE_LOG(LogTemp, Warning, TEXT("up = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
	// 하
	if (idx / hCount < vCount - 1)
	{
		n = idx + hCount;
		UE_LOG(LogTemp, Warning, TEXT("down = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
	// 좌
	if (idx % hCount > 0)
	{
		n = idx - 1;
		UE_LOG(LogTemp, Warning, TEXT("left = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
	// 우
	if (idx % hCount < hCount - 1)
	{
		n = idx + 1;
		UE_LOG(LogTemp, Warning, TEXT("right = %d"), n);
		cardWidgets[n]->SetBrushColor(FLinearColor::Red);
	}
}
