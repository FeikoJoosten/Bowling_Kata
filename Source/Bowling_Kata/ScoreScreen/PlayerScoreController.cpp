// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScoreController.h"
#include "ScoresUtils.h"

int maximumAllowedRolls;

void UPlayerScoreController::Setup(FText playerName) {
	playerNameText->SetText(playerName);
	for (int i = 0; i < ScoresUtils::NumberOfTurns - 1; i++) { // Hard coding the player score elements to init 9 items as that's the number of regular score elements in a bowling match
		UPlayerScoreElement* element = CreateWidget<UPlayerScoreElement>(scoresHolder, playerScoreElement, FName(FString("ScoreElement_" + i)));
		element->Setup();
		scoresHolder->AddChildToHorizontalBox(element);
		scoreElements.Add(element);
	}

	UPlayerScoreFinalElement* finalElement = CreateWidget<UPlayerScoreFinalElement>(scoresHolder, playerScoreFinalElement, FName(FString("ScoreFinalElement")));
	finalElement->Setup();
	scoresHolder->AddChildToHorizontalBox(finalElement);
	scoreElements.Add(finalElement);

	totalScoreElement = CreateWidget<UPlayerTotalScoreElement>(scoresHolder, playerTotalScoreElement, FName(FString("TotalScoreElement")));
	totalScoreElement->Setup();
	scoresHolder->AddChildToHorizontalBox(totalScoreElement);

	currentPinsRemaining = ScoresUtils::NumberOfPinsAtStartOfRound;
}

void UPlayerScoreController::ProcessRoll(int rolledPins) {
	if (currentScoreIndex >= ScoresUtils::NumberOfTurns) return;

	currentPinsRemaining -= rolledPins;;
	for (int i = 0; i <= currentScoreIndex; ++i) {
		scoreElements[i]->ProcessRoll(rolledPins, currentPinsRemaining);
	}
	rollsTakenThisTurn++;

	totalScoreElement->UpdateTotalScore(GetTotalScore());
	if (currentScoreIndex != ScoresUtils::NumberOfTurns - 1) return; // Final turn
	if (currentPinsRemaining > 0) return;

	maximumAllowedRolls = ScoresUtils::NumberOfRollsInFinalTurn; // Thrown a strike or spare during last round
	currentPinsRemaining = ScoresUtils::NumberOfPinsAtStartOfRound;
}

void UPlayerScoreController::PrepareForNextRound() {
	currentPinsRemaining = ScoresUtils::NumberOfPinsAtStartOfRound;
	maximumAllowedRolls = ScoresUtils::NumberOfRollsPerTurn;
	rollsTakenThisTurn = 0;
	currentScoreIndex++;
}

int UPlayerScoreController::GetTotalScore() {
	int totalScore = 0;
	for (int i = 0; i < scoreElements.Num(); ++i) {
		totalScore += scoreElements[i]->GetTotalScore();
	}
	return totalScore;
}

bool UPlayerScoreController::CanStillRoll() const {
	return rollsTakenThisTurn < maximumAllowedRolls && currentPinsRemaining > 0;
}

int UPlayerScoreController::GetNumberOfPinsRemaining() const {
	return currentPinsRemaining;
}

FText UPlayerScoreController::GetPlayerName() const {
	return playerNameText->GetText();
}
