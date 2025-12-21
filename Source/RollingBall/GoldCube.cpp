// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldCube.h"

// Sets default values
AGoldCube::AGoldCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	RootComponent = SceneComponent;	//Pongo el scene component como root
	MyMesh->SetupAttachment(RootComponent);	//Mantengo el root y a mi myMesh le pongo como hijo del root
}

// Called when the game starts or when spawned
void AGoldCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorWorldRotation(MyRotator * DeltaTime); // Que solo rote en el eje z
}