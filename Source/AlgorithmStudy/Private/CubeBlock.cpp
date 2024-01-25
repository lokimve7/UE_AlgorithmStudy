// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBlock.h"
#include <Components/WidgetComponent.h>
#include <Components/Border.h>
#include <Components/TextBlock.h>

// Sets default values
ACubeBlock::ACubeBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeBlock::BeginPlay()
{
	Super::BeginPlay();
	
	// widget component 찾아오자
	UWidgetComponent* widget = GetComponentByClass<UWidgetComponent>();
	UUserWidget* costWidget = widget->GetUserWidgetObject();

	//costWidget 에 배치되어 있는 위젯을 가져오자
	outLine = Cast<UBorder>(costWidget->GetWidgetFromName(TEXT("OutLine")));
	sCost = Cast<UTextBlock>(costWidget->GetWidgetFromName(TEXT("sCost")));
	gCost = Cast<UTextBlock>(costWidget->GetWidgetFromName(TEXT("gCost")));
	tCost = Cast<UTextBlock>(costWidget->GetWidgetFromName(TEXT("tCost")));
}

// Called every frame
void ACubeBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeBlock::SetCost(class ACubeBlock* s, class ACubeBlock* g)
{
	// 이전 cubeBlock 의 위치
	FVector sPos = s->GetActorLocation();
	// 목적지 cubeBlock 의 위치
	FVector gPos = g->GetActorLocation();
	// 현재 나의 위치
	FVector myPos = GetActorLocation();

	// sCost 구하자
	sCostValue = FMath::Abs(sPos.X - myPos.X) + FMath::Abs(sPos.Y - myPos.Y);
	sCostValue += s->sCostValue;

	// gCost 구하자
	float gCostValue = FMath::Abs(gPos.X - myPos.X) + FMath::Abs(gPos.Y - myPos.Y);

	// tCost 구하자
	tCostValue = sCostValue + gCostValue;

	// 각 Cost 를 UI 에 표현하자
	sCost->SetText(FText::AsNumber(sCostValue));
	gCost->SetText(FText::AsNumber(gCostValue));
	tCost->SetText(FText::AsNumber(tCostValue));

	// OutLine Color 파란색으로 하자
	SetColor(FLinearColor::Blue);
}

void ACubeBlock::SetColor(FLinearColor color)
{
	outLine->SetBrushColor(color);
}

