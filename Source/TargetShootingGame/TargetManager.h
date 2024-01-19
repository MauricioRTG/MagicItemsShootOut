// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetManager.generated.h"

UCLASS()
class TARGETSHOOTINGGAME_API ATargetManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	/*Form the Available targets randomly select the ones we want to activate and store them in the ActiveTargets array*/
	void RandomlySelectActiveTargets();

	UFUNCTION()
	/*Unhide targets in scene from the ActiveTargets array*/
	void UnhideTargets();

	UFUNCTION()
	/*Hide Targets*/
	void HideTargets();

	UFUNCTION()
	/*Initialize AvailableTargets array, by obtaining from the level all the actors that have a ATarget class*/
	void InitializeAvailableTargets();

	UFUNCTION()
	/*Remove active target from ActiveTargets array*/
	void RemoveActiveTarget(class ATarget* Target);

	UFUNCTION()
	/*Remove available target from AvailableTargets array*/
	void RemoveAvailableTarget(class ATarget* Target);

	UFUNCTION()
	/*Select new set of targets to unhide*/
	void SelectNewSetOfTargetsToUnhide();

	UFUNCTION()
	void StartHideTargetsTimer();

	UFUNCTION()
	void StartUnhideTargetsTimer();

	UFUNCTION()
	void StopHideTargetsTimer();
	
	UFUNCTION()
	void StopUnhideTargetsTimer();

	UFUNCTION()
	void EmptyActiveTargets();

	UFUNCTION()
	void EmptyAvailableTargets();

private:
	/*All targets in game*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AvailableTargets;

	/*Targets that are going to be unhide in game*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	TArray<class ATarget*> ActiveTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATarget> TargetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	int32 AmountOfRandomSelectedTargets;

	/*Call SelectNewSetOfTargetsToUnhide once per the specified time interval*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	float TimeIntervalForNewTargets;

	/*Call UnhideTargets once per the specified determined time interval*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	float TimeIntervalToUnhideTargets;

	/*Call SelectNewSetOfTargetsToUnhide starting the specified delay from now*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	float UnhideTargetsInFirstDelay;

	/*Call UnhideTargets starting the specified delay from now*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targets", meta = (AllowPrivateAccess = "true"))
	float NewTargetsInFirstDelay;

	/*TimerHandle for the function SelectNewSetOfTargetsToUnhide*/
	FTimerHandle NewSetTargetsTimerHandle;

	/*TimerHandle for the function UnhideTargets*/
	FTimerHandle UnhideTargetsTimerHandle;
};
