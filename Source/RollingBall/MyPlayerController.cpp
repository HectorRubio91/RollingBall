// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Ball.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerController::OnLoseLife()
{
	
	if (CurrentLives > 1)
	{
		UGameplayStatics::SpawnSound2D(GetWorld(), DeathSound);
		// Aviso a BPs que actualize el texto
		CurrentLives--;
		UpdateUILives(CurrentLives);
		
		// Actualizo el temporizador al maximo
		CurrentTime = MaxTime;
		UpdateUITime(CurrentTime);
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyPlayerController::UpdateTimer, 1.0f, true);
		
		//Separa la bola del controlador, el controlador queda libre
		UnPossess();
		//Se comunica al GameMode que resetee el controlador, la bola se pone en el PlayerStart
		GetWorld()->GetAuthGameMode()->RestartPlayer(this);
	} else
	{
		GameOver();
	}
}

void AMyPlayerController::GameOver()
{
	//Mostrar raton para poder salir de la pantalla
	bShowMouseCursor = true;

	//Mostrar widget de game over
	auto MyWidget = CreateWidget(this, GameOverWidgetClass);
	MyWidget->AddToViewport();
}

void AMyPlayerController::UpdateScore()
{
	CurrentScore++;
	UpdateUIScore(CurrentScore);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto Input = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Input->AddMappingContext(MyMappingContext, 0);
	
	CurrentTime = MaxTime;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyPlayerController::UpdateTimer, 1.0f, true);
	
	UpdateUITime(CurrentTime);
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABall* BallPawn = Cast<ABall>(InPawn);
	//El PlayerController nace y le comunica a la bola quien la controla
	BallPawn->SetBallController(this);
}

void AMyPlayerController::UpdateTimer()
{
	
	CurrentTime--;
	UpdateUITime(FMath::Max(CurrentTime, 0.f)); 
	
	if (CurrentTime <= 0)
	{
		OnTimeOver();
	}
}

void AMyPlayerController::OnTimeOver()
{
	
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	OnLoseLife();
}

void AMyPlayerController::AddTime(float ExtraTime)
{
	
	CurrentTime += ExtraTime;
	
	if (CurrentTime > MaxTime)
	{
		CurrentTime = MaxTime;
	}
	
	UpdateUITime(CurrentTime);
}