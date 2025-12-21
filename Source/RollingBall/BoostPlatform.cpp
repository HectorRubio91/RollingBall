// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostPlatform.h"
#include "Ball.h"

// Sets default values
ABoostPlatform::ABoostPlatform()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);

}

void ABoostPlatform::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	ABall* Ball = Cast<ABall>(OtherActor);
	if (Ball)
	{
		FVector Direction = GetActorForwardVector();
		Ball->ApplyImpulse(Direction * BoostForce);
	}
	
}

