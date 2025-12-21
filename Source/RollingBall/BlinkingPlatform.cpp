// Fill out your copyright notice in the Description page of Project Settings.


#include "BlinkingPlatform.h"

// Sets default values
ABlinkingPlatform::ABlinkingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	
	SetRootComponent(Root);
	PlatformMesh->SetupAttachment(Root);
	PlatformMesh->SetMassOverrideInKg(NAME_None, 1000000);
}

// Called when the game starts or when spawned
void ABlinkingPlatform::BeginPlay()
{
	Super::BeginPlay();
	//TimerHandler, Object, (duenio), delegado, time, loop?
	GetWorldTimerManager().SetTimer(BlinkTimerHandle, this, &ABlinkingPlatform::Blink, 2, true);
}

// Called every frame
void ABlinkingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Detener el timer
	//GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
}

void ABlinkingPlatform::Blink()
{
	//PlatformMesh->SetHiddenInGame();
	//PlatformMesh->SetActive();

	//PlatformMesh->SetVisibility(!PlatformMesh->IsVisible());
	if (bStartsVisible)
	{
		PlatformMesh->SetVisibility(false);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bStartsVisible = false;
	} else
	{
		PlatformMesh->SetVisibility(true);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		bStartsVisible = true;
	}
}