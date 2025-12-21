// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

#include "Components/SplineComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));

	SetRootComponent(Root);
	PlatformMesh->SetupAttachment(Root);
	Spline->SetupAttachment(Root);
	PlatformMesh->SetSimulatePhysics(true);
	PlatformMesh->SetMassOverrideInKg(NAME_None, 100000000);
	PlatformMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SplinePointsNum = Spline->GetNumberOfSplinePoints();
	CalculateNewDestination();
	//Como rb.linearVelocity en Unity
	PlatformMesh->SetPhysicsLinearVelocity(CurrentDirection * Speed);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FVector::Dist(PlatformMesh->GetComponentLocation(), CurrentDestination) < 5.0f)
	{
		CalculateNewDestination();
		//Como rb.linearVelocity en Unity
		PlatformMesh->SetPhysicsLinearVelocity(CurrentDirection * Speed);
	}
}

void AMovingPlatform::CalculateNewDestination()
{
	CurrentDestination = Spline->GetLocationAtSplinePoint(CurrentPointIndex, ESplineCoordinateSpace::World);
	//Sacar la dirección de CurrentDestination	-- GetSafeNormal() es como .normalized en Unity
	CurrentDirection = (CurrentDestination - PlatformMesh->GetComponentLocation()).GetSafeNormal();
	
	//Asegurarse de no salirse de los puntos del spline
	CurrentPointIndex = (CurrentPointIndex + 1) % SplinePointsNum;
}