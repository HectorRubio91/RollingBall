// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldCube.generated.h"

UCLASS()
class ROLLINGBALL_API AGoldCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoldCube();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Es como un empty game object en Unity
	UPROPERTY(EditDefaultsOnly, Category= "My data")
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, Category= "My data")
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere, Category= "My data")
	FRotator MyRotator;
};