// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerScoreElement.generated.h"

/**
 *
 */
UCLASS()
class BOWLING_KATA_API UPlayerScoreElement : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Setup();

	int GetTotalScore() const;
	int GetNumberOfRollsLeftToProcess() const;
	virtual void ProcessRoll(int pinsRolled, int pinsRemaining);
	
protected:
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UTextBlock* firstScoreText;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UTextBlock* secondScoreText;
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UTextBlock* totalScoreText;

	int numberOfRollsLeftToProcess;
	int totalScore;
	TArray<UTextBlock*> scoreTexts;

	inline static const FText strikeText = FText::FromString("X");
	inline static const FText spareText = FText::FromString("/");
	inline static const FText dashText = FText::FromString("-");
};
