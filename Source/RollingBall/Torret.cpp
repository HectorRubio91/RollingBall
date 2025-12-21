// Fill out your copyright notice in the Description page of Project Settings.


#include "Torret.h"

#include "Projectile.h"
#include "Components/SphereComponent.h"

// Sets default values
ATorret::ATorret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	TurretTower = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphere"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	
	//Jerarquia
	SetRootComponent(TurretBase);
	TurretTower->SetupAttachment(GetRootComponent());
	RangeSphere->SetupAttachment(GetRootComponent());
	ProjectileSpawnPoint->SetupAttachment(TurretTower);
}

// Called when the game starts or when spawned
void ATorret::BeginPlay()
{
	Super::BeginPlay();
	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATorret::OnOverlap);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATorret::OnEndOverlap);
}

//Funcion encargada de spawnear los proyectiles
void ATorret::SpawnProjectile() const
{
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
}

// Called every frame
void ATorret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetActor != nullptr)
	{
		//Se obtiene la direccion a target
		FVector DistanceToTarget = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		
		//Se obtiene dicha direccion
		FVector InterpVector = FMath::VInterpTo(TurretTower->GetForwardVector(), DistanceToTarget, DeltaTime, RotationSpeed);
		
		//Obtienes la rotacion de dicha direccion
		FRotator RotationToTarget = InterpVector.Rotation();

		//La torreta gira en la direccion correcta
		TurretTower->SetWorldRotation(FRotator(0, RotationToTarget.Yaw, 0));
	}
}

void ATorret::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		TargetActor = OtherActor;

		//Spawnear proyectiles cada x tiempo
		GetWorldTimerManager().SetTimer(FireRateTimer, this, &ATorret::SpawnProjectile, FireRate, true);
	}
}

void ATorret::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		TargetActor = nullptr;
		GetWorldTimerManager().ClearTimer(FireRateTimer);
	}
}