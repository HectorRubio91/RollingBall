// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torret.generated.h"

class USphereComponent;

UCLASS()
class ROLLINGBALL_API ATorret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category= "Components")
	UStaticMeshComponent* TurretBase;
	UPROPERTY(EditDefaultsOnly, Category= "Components")
	UStaticMeshComponent* TurretTower;

	UPROPERTY(EditAnywhere, Category= "Components")
	USceneComponent* ProjectileSpawnPoint;
	
	//Trigger en forma de esfera
	UPROPERTY(EditDefaultsOnly, Category= "Components")
	USphereComponent* RangeSphere;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly, Category= "Data")
	float RotationSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category= "Data")
	float FireRate = 2.f;
	
	UPROPERTY(EditDefaultsOnly, Category= "Data")
	TSubclassOf<class AProjectile> ProjectileClass;

	FTimerHandle FireRateTimer;
	
	void SpawnProjectile() const;
};