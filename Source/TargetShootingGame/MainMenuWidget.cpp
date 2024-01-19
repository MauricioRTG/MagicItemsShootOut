// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "TargetShootingGameGameModeBase.h"
#include "TargetManager.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnStartGameButtonClicked);
}

void UMainMenuWidget::OnStartGameButtonClicked()
{
	//Get player controller reference
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//Interact with game elements only, and don't show cursos
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}

	
	//Start GameMode's set minutes and seconds timer
	ATargetShootingGameGameModeBase* GameMode = Cast<ATargetShootingGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		//Spawn Target Manager
		GameMode->SpawnTargetManager();

		GameMode->StartTimer();
		//Start TimeManager Hide and unhide targets timer
		if (ATargetManager* TargetManager = GameMode->TargetManager)
		{
			//TargetManager->StartHideTargetsTimer();
			TargetManager->StartUnhideTargetsTimer();
			TargetManager->StartHideTargetsTimer();
		}
	}

	//Get PlayerCharacter reference
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		//Show HUD widgets
		PlayerCharacter->ShowHUD();
		PlayerCharacter->ShowScore();
		PlayerCharacter->ShowCrosshair();
	}

	//Remove widget from viewport
	RemoveFromParent();

	//Destruct instance
	Destruct();
}
