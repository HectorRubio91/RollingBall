// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlinkingPlatform.generated.h"

UCLASS()
class ROLLINGBALL_API ABlinkingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlinkingPlatform();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	void Blink();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category= "Component")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category= "Component")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly, Category= "Data")
	FTimerHandle BlinkTimerHandle;

	UPROPERTY(EditInstanceOnly, Category= "Data")
	bool bStartsVisible;
};