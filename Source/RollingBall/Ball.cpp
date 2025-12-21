// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABall::ABall()
{
	//auto Ejemplo = 0; // No hace falta el var de tipo en C++ si se usa auto
	//Ejemplo = 3.5f; // Da error porque no se puede convertir
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Es similar a GetComponent de Unity
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	//Jerarquia de componentes
	RootComponent = MyMesh;
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	MyMesh->SetSimulatePhysics(true);
	MyMesh->SetMassOverrideInKg(NAME_None, 100);
}

void ABall::SetBallController(AMyPlayerController* MyPlayerController)
{
	this->BallController = MyPlayerController;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ABall::OnDamageTaken);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->ActorHasTag("Coin"))
	{
		BallController->UpdateScore();
		OtherActor->Destroy();
	}
	else if (OtherActor->ActorHasTag("DeathZone"))
	{
		//Se comunica al controlador que ha perdido vida y se destruye
		BallController->OnLoseLife();
		Destroy();
	}
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movimiento player
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		//Cuando MoveAction este en triggered, la función Move se va a ejecutar
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABall::Move);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABall::Jump);
	}
}

void ABall::Move(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning,TEXT("Moving"));
	FVector2D InputVector = InputActionValue.Get<FVector2D>();

	MyMesh->AddForce(FVector(InputVector.Y, InputVector.X, 0) * Force);
	
}

void ABall::Jump(const FInputActionValue& InputActionValue)
{
	auto RayEnd = GetActorLocation() + MyMesh->GetCollisionShape().GetExtent().Z * FVector::DownVector;

	DrawDebugLine(GetWorld(), GetActorLocation(), RayEnd, FColor::Red, false, 2);

	if (GetWorld()->LineTraceTestByChannel(GetActorLocation(), RayEnd, ECC_GameTraceChannel1))
	{
		UGameplayStatics::SpawnSound2D(GetWorld(), JumpSound);
		//UGameplayStatics::SpawnEmitterAtLocation()
		MyMesh->AddImpulse(FVector::UpVector * JumpForce);
	}
}

void ABall::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	BallController->OnLoseLife();
	this->Destroy();
}
