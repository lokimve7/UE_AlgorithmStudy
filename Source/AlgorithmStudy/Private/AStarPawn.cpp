// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPawn.h"
#include "CubeBlock.h"

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
	
	// 마우스 커서 보이게 하자
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void AAStarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (path.Num() > 0)
	{
		currTime += DeltaTime;
		if (currTime > 0.5f)
		{
			currTime = 0;

			SetActorLocation(path[0]);
			path.RemoveAt(0);

			if (path.Num() == 0)
			{
				// 초기화
				for(int32 i = 0; i < openArray.Num(); i++)
					openArray[i]->SetInit();
				for(int32 i = 0; i < closeArray.Num(); i++)
					closeArray[i]->SetInit();

				openArray.Empty();
				closeArray.Empty();
			}
		}
	}
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
		startCube = Cast<ACubeBlock>(hit.GetActor());

		openArray.Add(startCube);
	}

	// Goal Cube 를 알아오자

	FVector mouseDir;
	// 마우스 클릭위치를 3D 공간의 좌표로 바꾸자
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(start, mouseDir);

	goal = start + mouseDir * 100000;

	result =GetWorld()->LineTraceSingleByChannel(hit, start, goal, ECC_Visibility, parmas);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("goal : %s"), *hit.GetActor()->GetActorLabel());
		goalCube = Cast<ACubeBlock>(hit.GetActor());
	}

	FindPath();
}

void AAStarPawn::FindPath()
{
	// 기준이 되는 Cube 설정
	currCube = openArray[0];

	openArray.RemoveAt(0);

	// 오른쪽
	AddOpen(FVector::RightVector);
	// 위 (앞)
	AddOpen(FVector::ForwardVector);
	// 왼쪽
	AddOpen(FVector::LeftVector);
	// 아래 (뒤)
	AddOpen(FVector::BackwardVector);

	// 기준이 되는 Cube 를 openArray 에서 빼고, closeArray 에 넣자
	
	closeArray.Add(currCube);
	// closeArray outline 을 빨간색으로
	currCube->SetColor(FLinearColor::Red);

	// 목적지까지 잘 찾아갔다면?
	if (openArray[0] == goalCube || openArray.Num() == 0)
	{
		// 길을 찾은 것임 (노란색으로 OutLine 변경)

		// 부모 CubeBlock 없을 때까지 반복

		ACubeBlock* tempCube = goalCube;

		while (tempCube->parentCube != nullptr)
		{
			// 가야하는 길 추가
			path.Insert(tempCube->GetActorLocation(), 0);

			tempCube->SetColor(FLinearColor::Yellow);
			tempCube = tempCube->parentCube;
		}
	}
	else
	{
		FindPath();
	}
}

void AAStarPawn::AddOpen(FVector dir)
{
	// dir 방향으로 Cube 가 있는 검출 (LineTrace)
	FHitResult hit;
	FVector start, end;
	FCollisionQueryParams params;
	params.AddIgnoredActor(currCube);
	params.AddIgnoredActor(this);

	start = currCube->GetActorLocation();
	end = start + dir * 100;

	bool result = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, params);
	if (result == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : %s"), *dir.ToString(), *hit.GetActor()->GetActorLabel());

		
		ACubeBlock* cube = Cast<ACubeBlock>(hit.GetActor());
		// openArray, closeArray 해당 Cube 가 없으면 
		if (openArray.Contains(cube) == false && closeArray.Contains(cube) == false)
		{
			// 해당 Cube 의 Cost 구하자
			cube->SetCost(currCube, goalCube);

			// openArray 값을 넣자 (나보다 Cost 큰 Cube 앞에)
			int32 i = 0;
			for (i = 0; i < openArray.Num(); i++)
			{				
				if (openArray[i]->tCostValue >= cube->tCostValue)
				{
					break;
				}
			}
			openArray.Insert(cube, i);
		}
	}	
	
}

