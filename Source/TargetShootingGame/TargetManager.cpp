// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetManager.h"
#include "Target.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/TimerHandle.h"

// Sets default values
ATargetManager::ATargetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NewTargetsInFirstDelay = 2.0f;
	UnhideTargetsInFirstDelay = 2.0f;

	TimeIntervalForNewTargets = 10.0f;
	TimeIntervalToUnhideTargets = 5.0f;

	TargetClass = ATarget::StaticClass();
	AmountOfRandomSelectedTargets = 3;
}

// Called when the game starts or when spawned
void ATargetManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeAvailableTargets();
	//Hide all targets by default in scene
	HideTargets();
}

// Called every frame
void ATargetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetManager::RandomlySelectActiveTargets()
{
	int32 RandomIndex;

	//Checks if AvailableTargets array is empty
	if (AvailableTargets.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("Available Targets is empty"))
		return;
	}

	//Clamps the AmountOfRandomSelectedTargets to range only from 0 to AvailableTargets elements count
	if (AmountOfRandomSelectedTargets > AvailableTargets.Num())
	{
		AmountOfRandomSelectedTargets = AvailableTargets.Num();
	}
	else if (AmountOfRandomSelectedTargets < 0)
	{
		AmountOfRandomSelectedTargets = 0;
	}

	//Select an especified amount of Targets from the AvailableTargets Array
	for (int i = 0; i < AmountOfRandomSelectedTargets; i++)
	{
		//Select a new random index until ActiveTargets array doesn't contain the selected target to avoid repeating the same selected target
		do
		{
			//Select a random index from AvailableTargets
			RandomIndex = FMath::RandRange(0, AvailableTargets.Num() - 1);

		} while (ActiveTargets.Contains(Cast<ATarget>(AvailableTargets[RandomIndex])));

		//Add the selected target from index to the ActiveTargets (it makes sure is a ATarget)
		ATarget* SelectedTarget = Cast<ATarget>(AvailableTargets[RandomIndex]);
		if (SelectedTarget)
		{
			ActiveTargets.Add(SelectedTarget);
		}
	}
}

void ATargetManager::UnhideTargets()
{
	if (AvailableTargets.IsEmpty()) { return; }

	//Iterate through the ActiveTargets array an unhide randomly selected targets in game and enable collision
	for (auto& Target : ActiveTargets)
	{
		if (Target != nullptr) 
		{
			Target->SetActorHiddenInGame(false);
			Target->SetActorEnableCollision(true);
		}
	}

	//StartHideTargetsTimer();
}

void ATargetManager::HideTargets()
{
	if (AvailableTargets.IsEmpty()) { return;  }

	//Iterate through the AvailableTargets array an hide the targets in game and disable collision
	for (auto& Target : AvailableTargets)
	{
		if (Target != nullptr)
		{
			Target->SetActorHiddenInGame(true);
			Target->SetActorEnableCollision(false);
		}
	}
}

void ATargetManager::InitializeAvailableTargets()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, AvailableTargets);
	UE_LOG(LogTemp, Log, TEXT("Available Targets: %i"), AvailableTargets.Num());
}

void ATargetManager::RemoveActiveTarget(ATarget* Target)
{
	if (ActiveTargets.Contains(Target))
	{
		int32 TargetIndex = ActiveTargets.IndexOfByKey(Target);
		ActiveTargets.RemoveAt(TargetIndex);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ActiveTargets array doesn't contain target"));
	}
	
}

void ATargetManager::RemoveAvailableTarget(ATarget* Target)
{
	
	if (AvailableTargets.Contains(Target))
	{
		int32 TargetIndex = AvailableTargets.IndexOfByKey(Target);
		AvailableTargets.RemoveAt(TargetIndex);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AvailableTargets array doesn't contain target"));
	}
}

void ATargetManager::SelectNewSetOfTargetsToUnhide()
{
	if (AvailableTargets.IsEmpty()) { return; }

	//Hide targets
	HideTargets();

	//Remove all elements from activeTargets.
	ActiveTargets.Empty();

	//Select new active targets
	RandomlySelectActiveTargets();

	//StartUnhideTargetsTimer();
}

void ATargetManager::StartHideTargetsTimer()
{
	//Now set a timer to call SelectNewSetOfTargetsToUnhide function once per TimeIntervalForNewTargets, starting NewTargetsInFirstDelay from now
	GetWorldTimerManager().SetTimer(NewSetTargetsTimerHandle, this, &ATargetManager::SelectNewSetOfTargetsToUnhide, TimeIntervalForNewTargets, true, NewTargetsInFirstDelay);
}

void ATargetManager::StartUnhideTargetsTimer()
{
	//Now set a timer to call UnhideTargets function once per TimeIntervalToUnhideTargets, starting UnhideTargetsInFirstDelay from now
	GetWorldTimerManager().SetTimer(UnhideTargetsTimerHandle, this, &ATargetManager::UnhideTargets, TimeIntervalToUnhideTargets, true, UnhideTargetsInFirstDelay);
}

void ATargetManager::StopHideTargetsTimer()
{
	GetWorldTimerManager().ClearTimer(NewSetTargetsTimerHandle);
}

void ATargetManager::StopUnhideTargetsTimer()
{
	GetWorldTimerManager().ClearTimer(UnhideTargetsTimerHandle);
}

void ATargetManager::EmptyActiveTargets()
{
	ActiveTargets.Empty();
}

void ATargetManager::EmptyAvailableTargets()
{
	AvailableTargets.Empty();
}

