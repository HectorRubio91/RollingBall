#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedPlayerInput.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void OnLoseLife();
	void UpdateScore();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUILives(int32 NewLives);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUIScore(int32 NewScore);
	
protected:
	virtual void BeginPlay() override;

	//Este metodo se ejecuta cuando el controlador posee a un pawn
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY(EditAnywhere, Category= "Inputs")
	class UInputMappingContext* MyMappingContext;

	//Esta variable se expone por blueprints, obligatorio incluir lo de meta para que se quede privada
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "Data", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLives = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "Data", meta = (AllowPrivateAccess = "true"))
	int32 CurrentScore = 0;

	//Una clase, no una instancia
	UPROPERTY(EditAnywhere, Category= "Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	void GameOver();
};