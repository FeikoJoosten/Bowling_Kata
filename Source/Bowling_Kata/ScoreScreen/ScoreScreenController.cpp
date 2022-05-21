// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreScreenController.h"
#include "ScoresUtils.h"

void UScoreScreenController::NativeOnInitialized() {
	Super::NativeOnInitialized();

	addPlayerButton->OnClicked.AddDynamic(this, &UScoreScreenController::AddPlayer);
	startGameButton->OnClicked.AddDynamic(this, &UScoreScreenController::InitializeGame);
	nextRollButton->OnClicked.AddDynamic(this, &UScoreScreenController::SimulateNextRoll);

	playerSetupScreen->SetVisibility(ESlateVisibility::Visible);
	scoreScreen->SetVisibility(ESlateVisibility::Collapsed);
}

void UScoreScreenController::AddPlayer(){
	FText playerToAdd = playerToAddTextBox->GetText();
	if(playerToAdd.IsEmptyOrWhitespace()) {
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString("Please enter a name!"));
		return;
	}

	registeredPlayers.Add(playerToAdd);
	playerToAddTextBox->SetText(FText::GetEmpty());
}

void UScoreScreenController::InitializeGame() {
	if(registeredPlayers.Num() == 0) {
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString("Please register at least 1 player!"));
		return;
	}

	for (int i = 0; i < registeredPlayers.Num(); ++i) {
		FText playerToRegister = registeredPlayers[i];
		UPlayerScoreController* controller = CreateWidget<UPlayerScoreController>(playerScoresHolder, scoreControllerTemplate, FName(FString("playerScore: " + playerToRegister.ToString())));
		playerScoresHolder->AddChildToVerticalBox(controller);
		controller->Setup(playerToRegister);
		playerScores.Add(controller);
	}

	scoreScreen->SetVisibility(ESlateVisibility::Visible);
	playerSetupScreen->SetVisibility(ESlateVisibility::Collapsed);
	playerScores[0]->PrepareForNextRound();
}

void UScoreScreenController::SimulateNextRoll() {
	if (currentRound >= ScoresUtils::NumberOfTurns) return;

	UPlayerScoreController* controller = playerScores[currentPlayerIndex];
	const int pinsRolled = FMath::RandRange(0, controller->GetNumberOfPinsRemaining());
	//const int pinsRolled = 10;
	controller->ProcessRoll(pinsRolled);
	if (controller->CanStillRoll()) return;

	currentPlayerIndex++;
	if (currentPlayerIndex >= playerScores.Num()) {
		currentPlayerIndex = 0;
		currentRound++;
	}
	
	if (currentRound >= ScoresUtils::NumberOfTurns) {
		int highestScore = 0;
		TArray<UPlayerScoreController*> highestScoringPlayers;
		for (int i = 0; i < playerScores.Num(); ++i) {
			const int controllerScore = playerScores[i]->GetTotalScore();
			if (controllerScore < highestScore) continue;
			if (controllerScore > highestScore) highestScoringPlayers.Empty();

			highestScore = controllerScore;
			if (controllerScore == highestScore) highestScoringPlayers.Add(playerScores[i]);
		}

		// Output a victory message for all players that won
		for (UPlayerScoreController* playerController : highestScoringPlayers) {
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString(playerController->GetPlayerName().ToString() + " has won!"));
		}

		// TODO: Reset functionality?
	} else {
		playerScores[currentPlayerIndex]->PrepareForNextRound();
	}
}
