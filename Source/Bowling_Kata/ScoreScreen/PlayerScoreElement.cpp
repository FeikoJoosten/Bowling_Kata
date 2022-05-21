#include "PlayerScoreElement.h"
#include "ScoresUtils.h"

void UPlayerScoreElement::Setup() {
	numberOfRollsLeftToProcess = ScoresUtils::NumberOfRollsPerTurn;
	firstScoreText->SetText(FText::GetEmpty());
	secondScoreText->SetText(FText::GetEmpty());
	totalScoreText->SetText(FText::GetEmpty());

	scoreTexts.Add(firstScoreText);
	scoreTexts.Add(secondScoreText);
}

int UPlayerScoreElement::GetTotalScore() const {
	return totalScore;
}

int UPlayerScoreElement::GetNumberOfRollsLeftToProcess() const {
	return numberOfRollsLeftToProcess;
}

void UPlayerScoreElement::ProcessRoll(int pinsRolled, int pinsRemaining) {
	if (numberOfRollsLeftToProcess <= 0) return;

	if (pinsRemaining == 0 && (numberOfRollsLeftToProcess == ScoresUtils::NumberOfRollsPerTurn || numberOfRollsLeftToProcess == ScoresUtils::NumberOfRollsInFinalTurn)) {
		if (firstScoreText->GetText().IsEmptyOrWhitespace()) {
			firstScoreText->SetText(strikeText);
			secondScoreText->SetText(dashText);
			numberOfRollsLeftToProcess += 1; // Gain one additional roll to process
		}
	} else if (pinsRemaining == 0) {
		if (secondScoreText->GetText().IsEmptyOrWhitespace()) {
			secondScoreText->SetText(spareText);
			numberOfRollsLeftToProcess += 1; // Gain one additional roll to process
		}
	} else {
		for (int i = 0; i < scoreTexts.Num(); ++i) {
			if (!scoreTexts[i]->GetText().IsEmptyOrWhitespace()) continue;
			scoreTexts[i]->SetText(pinsRolled > 0 ? FText::AsNumber(pinsRolled) : dashText);
			break;
		}
	}

	numberOfRollsLeftToProcess--;
	totalScore += pinsRolled;
	totalScoreText->SetText(FText::AsNumber(totalScore));
}
