// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "PlayerScoreElement.h"
#include "PlayerScoreFinalElement.h"
#include "PlayerTotalScoreElement.h"
#include "PlayerScoreController.generated.h"

/**
 *
 */
UCLASS()
class BOWLING_KATA_API UPlayerScoreController : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(FText playerName);
	void ProcessRoll(int rolledPins);
	void PrepareForNextRound();

	int GetTotalScore();
	bool CanStillRoll() const;
	int GetNumberOfPinsRemaining() const;
	FText GetPlayerName() const;

private:
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UTextBlock* playerNameText;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UHorizontalBox* scoresHolder;
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<UPlayerScoreElement> playerScoreElement;
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<UPlayerScoreFinalElement> playerScoreFinalElement;
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<UPlayerTotalScoreElement> playerTotalScoreElement;

	int currentScoreIndex = -1;
	int currentPinsRemaining;
	int rollsTakenThisTurn;
	TArray<UPlayerScoreElement*> scoreElements;
	UPlayerTotalScoreElement* totalScoreElement;
};
