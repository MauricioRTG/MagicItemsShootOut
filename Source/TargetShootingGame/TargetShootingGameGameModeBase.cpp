// Copyright Epic Games, Inc. All Rights Reserved.


#include "TargetShootingGameGameModeBase.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "TargetManager.h"

ATargetShootingGameGameModeBase::ATargetShootingGameGameModeBase()
{
	TargetManagerClass = ATargetManager::StaticClass();

	//Set Minutes and Seconds for timer countdown
	Seconds = 10;
	Minutes = 1;
}

void ATargetShootingGameGameModeBase::Tick(float DeltaSeconds)
{
	
}

void ATargetShootingGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATargetShootingGameGameModeBase::SetMinutesAndSeconds()
{
	//If seconds is equal to 0 decrese minutes, else decrese Seconds by one
	if (Seconds == 0)
	{
		//if Minutes is equal to 0 pause game, else decrese Minutes
		if (Minutes == 0)
		{
			//Start game over
			GameOver();
		}
		else
		{
			Seconds = 59;
			Minutes -= 1;
		}
	}
	else
	{
		Seconds -= 1;
	}

	UE_LOG(LogTemp, Log, TEXT("%i : %i"), Minutes, Seconds);
}

void ATargetShootingGameGameModeBase::GameOver()
{
	//Pause game
	/*APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->SetPause(true);
	}*/

	//Stop timers 
	StopTimer();
	TargetManager->StopHideTargetsTimer();
	TargetManager->StopUnhideTargetsTimer();
	
	//Hide targets
	TargetManager->HideTargets();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		//Remove HUD widget from viewport
		PlayerCharacter->HideHUD();
		PlayerCharacter->HideScore();
		PlayerCharacter->HideCrosshair();

		//Create EndGame widget
		PlayerCharacter->ShowEndGame();
	}
}

void ATargetShootingGameGameModeBase::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATargetShootingGameGameModeBase::SetMinutesAndSeconds, 1.0f, true);
}

void ATargetShootingGameGameModeBase::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void ATargetShootingGameGameModeBase::SpawnTargetManager()
{
	if (TargetManagerClass)
	{
		TargetManager = Cast<ATargetManager>(GetWorld()->SpawnActor(TargetManagerClass));
	}
}
