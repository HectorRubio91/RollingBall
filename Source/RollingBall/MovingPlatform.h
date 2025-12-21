// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class USplineComponent;

UCLASS()
class ROLLINGBALL_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
#pragma region Components
	UPROPERTY(EditDefaultsOnly, Category= "Component")
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category= "Component")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly, Category= "Component")
	USplineComponent* Spline;
#pragma endregion

	UPROPERTY(EditDefaultsOnly, Category= "My data")
	float Speed = 250.f;
	
	int32 SplinePointsNum, CurrentPointIndex;

	FVector CurrentDestination, CurrentDirection;
	
	void CalculateNewDestination();
};