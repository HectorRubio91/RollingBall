// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushingCillinder.generated.h"

UCLASS()
class ROLLINGBALL_API APushingCillinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushingCillinder();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category= "My data")
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category= "My data")
	UStaticMeshComponent* CylinderMesh;

	float impulseForce = 10000.0f;
};