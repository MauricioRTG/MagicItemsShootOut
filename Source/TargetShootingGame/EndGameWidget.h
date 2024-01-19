// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARGETSHOOTINGGAME_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartGameButton;

	UFUNCTION()
	void OnRestartGameButtonClicked();
};
