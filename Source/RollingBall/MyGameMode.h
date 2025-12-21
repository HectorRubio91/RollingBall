// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMyGameMode();
public:
UPROPERTY(EditAnywhere, Category= "My data")
	TSubclassOf<ABall> MyPawnClass;
	
};