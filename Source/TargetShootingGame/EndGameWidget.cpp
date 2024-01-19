// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TargetShootingGameGameModeBase.h"
#include "TargetManager.h"

void UEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartGameButton)
	{
		RestartGameButton->OnClicked.AddUniqueDynamic(this, &UEndGameWidget::OnRestartGameButtonClicked);
	}
}

void UEndGameWidget::OnRestartGameButtonClicked()
{
	//Get current level name
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	//Restart level
	UGameplayStatics::OpenLevel(GetWorld(), FName(CurrentLevelName));
}
