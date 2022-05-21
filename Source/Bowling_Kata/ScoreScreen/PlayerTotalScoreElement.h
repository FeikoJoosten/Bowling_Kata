// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerTotalScoreElement.generated.h"

/**
 * 
 */
UCLASS()
class BOWLING_KATA_API UPlayerTotalScoreElement : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UTextBlock* totalScoreText;

	void Setup();
	void UpdateTotalScore(int totalScore) const;
};
