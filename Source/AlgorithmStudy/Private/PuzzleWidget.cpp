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

	// sameCardIdx 초기화
	sameCardIdx.Empty();

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
	int32 hIndex = (int32)((mousePos.X - offsetX) / cardSize); // 가로 기준으로 몇번째
	int32 vIndex = (int32)((mousePos.Y - offsetY) / cardSize); // 세로 기준으로 몇번째
	int32 selectCardIdx = hIndex + vIndex * hCount;
		
	// 가로 번째 hCount 보다 크거나 같으면 함수를 나가자.
	// mousePos.X - offsetX 0 보다 작으면 함수를 나가자
	// 세로 번째 vCount 보다 크거나 같으면 함수를 나가자.
	// mousePos.Y - offsetY 0 보다 작으면 함수를 나가자
	if (hIndex >= hCount ||
		mousePos.X - offsetX < 0 ||
		vIndex >= vCount ||
		mousePos.Y - offsetY < 0)	return;

	UE_LOG(LogTemp, Warning, TEXT("select card = %d"), selectCardIdx);

	// 선택한 카드의 값 저장
	selectCardValue = cardValues[selectCardIdx];

	// sameCardIdx 에 selectCardIdx 넣자
	sameCardIdx.Add(selectCardIdx);

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
		//UE_LOG(LogTemp, Warning, TEXT("up = %d"), n);
		// n 번째 카드의 값이 선택한 카드의 값과 같니?
		SameValueCard(n);
	}
	// 하
	if (idx / hCount < vCount - 1)
	{
		n = idx + hCount;
		UE_LOG(LogTemp, Warning, TEXT("down = %d"), n);
		SameValueCard(n);
	}
	// 좌
	if (idx % hCount > 0)
	{
		n = idx - 1;
		UE_LOG(LogTemp, Warning, TEXT("left = %d"), n);
		SameValueCard(n);
	}
	// 우
	if (idx % hCount < hCount - 1)
	{
		n = idx + 1;
		UE_LOG(LogTemp, Warning, TEXT("right = %d"), n);
		SameValueCard(n);
	}
}

void UPuzzleWidget::SameValueCard(int32 idx)
{
	// 내가 선택한 카드와 값이 같니?
	if (selectCardValue == cardValues[idx])
	{
		// idx 가 이미 sameCardIdx 에 존재하니?
		if (sameCardIdx.Contains(idx) == true) return;

		// 색을 빨간색으로 바꾸자
		cardWidgets[idx]->SetBrushColor(FLinearColor::Red);

		// 같은 값을 가지고 있는 카드다!
		sameCardIdx.Add(idx);

		// idx 번째 카드 기준으로 상, 하, 좌, 우 검색
		FindNearCard(idx);
	}
}
