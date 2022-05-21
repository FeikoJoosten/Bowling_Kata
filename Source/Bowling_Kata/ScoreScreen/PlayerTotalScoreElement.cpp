// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTotalScoreElement.h"

void UPlayerTotalScoreElement::Setup() {
	totalScoreText->SetText(FText::AsNumber(0));
}

void UPlayerTotalScoreElement::UpdateTotalScore(int totalScore) const {
	totalScoreText->SetText(FText::AsNumber(totalScore));
}
