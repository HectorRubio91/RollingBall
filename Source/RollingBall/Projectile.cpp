// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	// Activar la simulación de impacto
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	
	RootComponent = ProjectileMesh;
	//Como el componente genera una logica, no tiene jerarquia
	ProjectileMovement->InitialSpeed = 1300.f;
	ProjectileMovement->MaxSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::ProjectileHit);
	//El sistema de particulas acompania al componente
	UGameplayStatics::SpawnEmitterAttached(TrailParticles, ProjectileMesh);
}

void AProjectile::ProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit"));
	this->Destroy();
	//El sistema de particulas spawnea en un punto
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, Hit.Location);
	UGameplayStatics::ApplyDamage(OtherActor, 10.f, nullptr, this, UDamageType::StaticClass());
}