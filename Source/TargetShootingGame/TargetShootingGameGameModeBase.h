// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TargetShootingGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TARGETSHOOTINGGAME_API ATargetShootingGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

public:

	ATargetShootingGameGameModeBase();

	UFUNCTION()
	void SetMinutesAndSeconds();

	UFUNCTION()
	int32 GetMinutes() { return Minutes; };

	UFUNCTION()
	int32 GetSeconds() { return Seconds; };

	UFUNCTION()
	void GameOver();

	UFUNCTION()
	void StartTimer();

	UFUNCTION()
	void StopTimer();

	UFUNCTION()
	void SpawnTargetManager();

	UPROPERTY()
	class ATargetManager* TargetManager;

private:
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	int32 Seconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	int32 Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Manager", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<class ATargetManager> TargetManagerClass;
};
