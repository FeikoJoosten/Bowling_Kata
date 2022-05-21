// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerScoreElement.h"
#include "PlayerScoreFinalElement.generated.h"

/**
 * 
 */
UCLASS()
class BOWLING_KATA_API UPlayerScoreFinalElement : public UPlayerScoreElement
{
	GENERATED_BODY()

public:
	virtual void Setup() override;
	virtual void ProcessRoll(int pinsRolled, int pinsRemaining) override;
	
private:
	UPROPERTY(EditInstanceOnly, meta = (BindWidget))
	UTextBlock* thirdScoreText = nullptr;
};
