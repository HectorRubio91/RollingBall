// Fill out your copyright notice in the Description page of Project Settings.


#include "PushingCillinder.h"

// Sets default values
APushingCillinder::APushingCillinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	SetRootComponent(Root);
	CylinderMesh->SetupAttachment(Root);
	CylinderMesh->SetSimulatePhysics(true);
	//Pongo la masa muy elevada para que no se le empuje
	CylinderMesh->SetMassOverrideInKg(NAME_None, 100);
	CylinderMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void APushingCillinder::BeginPlay()
{
	Super::BeginPlay();
	//En Unity: rb.AddTorque //Con el bool del final, la masa no se tiene en cuenta a la hora de ejercer la fuerza
	CylinderMesh->AddAngularImpulseInDegrees(FVector::UpVector * impulseForce, NAME_None, true);
}	

// Called every frame
void APushingCillinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}