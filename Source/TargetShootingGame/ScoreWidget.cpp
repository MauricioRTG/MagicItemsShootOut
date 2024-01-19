// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "TargetShootingGameGameModeBase.h"
#include "Components/TextBlock.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UScoreWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) { return false; }

	if (ScoreTextField)
	{
		//Check if world context exists
		UWorld* World = GetWorld();
		if (World)
		{
			//Makes sure there is a game mode
			ATargetShootingGameGameModeBase* GameMode = Cast<ATargetShootingGameGameModeBase>(World->GetAuthGameMode());
			if (GameMode)
			{
				ScoreTextField->TextDelegate.BindUFunction(this, "SetScoreTextField");
			}
		}
	}

	return true;
}

FText UScoreWidget::SetScoreTextField()
{
	UWorld* World = GetWorld();

	if (World)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
		if (PlayerCharacter)
		{
			//Return player score from player character
			return FText::FromString(FString::FromInt(PlayerCharacter->GetPlayerScore()));
		}
		else
		{
			return FText::FromString("NULL");
		}
	}

	return FText::FromString("NULL");
}
