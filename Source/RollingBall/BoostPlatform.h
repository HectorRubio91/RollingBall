// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostPlatform.generated.h"

UCLASS()
class ROLLINGBALL_API ABoostPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoostPlatform();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category="Boost")
	float BoostForce = 300000.f;
};