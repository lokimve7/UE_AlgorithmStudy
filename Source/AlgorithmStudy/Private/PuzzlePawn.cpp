// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePawn.h"
#include "PuzzleWidget.h"

// Sets default values
APuzzlePawn::APuzzlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UPuzzleWidget> tempWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_PuzzleWidget.BP_PuzzleWidget_C'"));
	if (tempWidget.Succeeded())
	{
		puzzleWidgetClass = tempWidget.Class;
	}
}

// Called when the game starts or when spawned
void APuzzlePawn::BeginPlay()
{
	Super::BeginPlay();
	
	// Puzzle Widget 띄우자
	puzzleWidget = CreateWidget<UPuzzleWidget>(GetWorld(), puzzleWidgetClass);
	puzzleWidget->AddToViewport();

	// 마우스 보이게 하자
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void APuzzlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

