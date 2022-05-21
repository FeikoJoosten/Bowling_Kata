// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/VerticalBox.h"
#include "PlayerScoreController.h"
#include "Components/EditableTextBox.h"
#include "ScoreScreenController.generated.h"

/**
 * 
 */
UCLASS()
class BOWLING_KATA_API UScoreScreenController : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<UPlayerScoreController> scoreControllerTemplate;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UEditableTextBox* playerToAddTextBox;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UButton* addPlayerButton;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UButton* startGameButton;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UVerticalBox* playerScoresHolder;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UWidget* playerSetupScreen;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UWidget* scoreScreen;

	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UButton* nextRollButton;

	const int totalPins = 10;
	int currentRemainingPins;
	int currentPlayerIndex;
	int currentRound;
	TArray<UPlayerScoreController*> playerScores;
	TArray<FText> registeredPlayers;

	UFUNCTION()
	void AddPlayer();
	UFUNCTION()
	void InitializeGame();
	UFUNCTION()
	void SimulateNextRoll();
};
