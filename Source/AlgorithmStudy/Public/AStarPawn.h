// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AStarPawn.generated.h"

UCLASS()
class ALGORITHMSTUDY_API AAStarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAStarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void InputLMouseDown();

	void FindPath();
	void AddOpen(FVector dir);

public:

	// 길찾기 시작 위치
	UPROPERTY(VisibleAnywhere)
	class ACubeBlock* startCube;

	// 길찾기 목적지 위치
	UPROPERTY(VisibleAnywhere)
	class ACubeBlock* goalCube;

	// 해당 Cube 기준으로 상, 하, 좌, 우를 검색
	UPROPERTY(VisibleAnywhere)
	class ACubeBlock* currCube;

	// 이 변수에 들어있는 Cube 들을 기준으로 상, 하, 좌, 우를 검색
	UPROPERTY(VisibleAnywhere)
	TArray<class ACubeBlock*> openArray;

	// 검색이 다 끝난 Cube
	UPROPERTY(VisibleAnywhere)
	TArray<class ACubeBlock*> closeArray;
};
