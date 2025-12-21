// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "MyPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Ball.generated.h"

UCLASS()
class ROLLINGBALL_API ABall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABall();
	void SetBallController(AMyPlayerController* MyPlayerController);
	void ApplyImpulse(const FVector& Impulse);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void NotifyActorBeginOverlap(AActor* OtherActor);

	void Move(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);

private:
#pragma region Components
	UPROPERTY(EditDefaultsOnly, Category= "Component")	//EditAnywhere, EditDefaultsOnly, EditInstanceOnly
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditDefaultsOnly, Category= "Component")
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditDefaultsOnly, Category= "Component")
	class UCameraComponent* Camera;
#pragma endregion
	
	UPROPERTY(EditDefaultsOnly, Category= "My data")
	float Force = 100000.f;

	UPROPERTY(EditDefaultsOnly, Category= "My data")
	float JumpForce = 10000.f;
	
	UPROPERTY(EditDefaultsOnly, Category= "My data")
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category= "My data")
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category= "My data")
	int DamageTaken;
	
	UPROPERTY(EditDefaultsOnly, Category= "Sounds")
	USoundBase* JumpSound;
	
	UPROPERTY(EditDefaultsOnly, Category= "Sounds")
	USoundBase* CoinSound;
	
	UPROPERTY()
	AMyPlayerController* BallController;

	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};