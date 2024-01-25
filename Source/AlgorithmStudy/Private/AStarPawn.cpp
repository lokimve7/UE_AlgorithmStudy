// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPawn.h"

// Sets default values
AAStarPawn::AAStarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAStarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAStarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAStarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("LeftMouse"), IE_Pressed, this, &AAStarPawn::InputLMouseDown);
}

void AAStarPawn::InputLMouseDown()
{
	// 길찾기 시작.....

	FHitResult hit;
	FVector start, goal;
	FCollisionQueryParams parmas;
	bool result;

	// Start Cube 를 알아오자 (나의 위치에서 아래방향으로 LineTrace 를 실행)
	start = GetActorLocation() + FVector::UpVector;
	goal = start + FVector::DownVector * 5;
	parmas.AddIgnoredActor(this);

	result = GetWorld()->LineTraceSingleByChannel(hit, start, goal, ECC_Visibility, parmas);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("start : %s"), *hit.GetActor()->GetActorLabel());
	}
}

