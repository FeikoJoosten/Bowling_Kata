// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScoreFinalElement.h"
#include "ScoresUtils.h"

void UPlayerScoreFinalElement::Setup() {
	Super::Setup();
	thirdScoreText->SetText(FText::GetEmpty());
	scoreTexts.Add(thirdScoreText);

	numberOfRollsLeftToProcess = ScoresUtils::NumberOfRollsPerTurn; // override numberOfRollsLeftToProcess after invoking the super, as the base class also defines numberOfRollsLeftToProcess
}

void UPlayerScoreFinalElement::ProcessRoll(int pinsRolled, int pinsRemaining) {
	// Don't invoke the super, as this frame functions differently
	if (numberOfRollsLeftToProcess <= 0) return;

	for (int i = 0; i < scoreTexts.Num(); ++i) {
		if (!scoreTexts[i]->GetText().IsEmptyOrWhitespace()) continue;

		if (pinsRolled == ScoresUtils::NumberOfPinsAtStartOfRound) {
			scoreTexts[i]->SetText(strikeText);
		} else if(pinsRemaining == 0) {
			scoreTexts[i]->SetText(spareText);
		} else {
			scoreTexts[i]->SetText(pinsRolled > 0 ? FText::AsNumber(pinsRolled) : dashText);
		}

		break;
	}

	if (pinsRemaining == 0 && ScoresUtils::NumberOfRollsPerTurn - numberOfRollsLeftToProcess == 0) {
		numberOfRollsLeftToProcess += 1; // Gain one additional roll as a strike or spare was thrown
	}

	numberOfRollsLeftToProcess--;
	totalScore += pinsRolled;
	totalScoreText->SetText(FText::AsNumber(totalScore));
}
