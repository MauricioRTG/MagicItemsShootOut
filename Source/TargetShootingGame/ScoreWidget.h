// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARGETSHOOTINGGAME_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreTextField;

	UFUNCTION(BlueprintCallable)
	FText SetScoreTextField();
};
