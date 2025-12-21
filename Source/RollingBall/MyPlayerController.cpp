// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Ball.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void AMyPlayerController::OnLoseLife()
{
	if (CurrentLives > 1)
	{
		//Avisar a BPs que actualize el texto
		CurrentLives--;
		UpdateUILives(CurrentLives);
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
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABall* BallPawn = Cast<ABall>(InPawn);
	//El PlayerController nace y le comunica a la bola quien la controla
	BallPawn->SetBallController(this);
}