// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TARGETSHOOTINGGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/*First Person Camera Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/*Mapping Context*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/*Look Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called for look input action
	void Look(const FInputActionValue &Value); 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void UpdateScore(int &Amount);

	UFUNCTION()
	void ShowHUD();

	UFUNCTION()
	void ShowMainMenu();

	UFUNCTION()
	void ShowEndGame();

	UFUNCTION()
	void HideHUD();

	UFUNCTION()
	void ShowScore();

	UFUNCTION()
	void HideScore();

	UFUNCTION()
	void ShowCrosshair();

	UFUNCTION()
	void HideCrosshair();

	UFUNCTION()
	int32 GetPlayerScore() { return PlayerScore; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Information", meta = (AllowPrivateAccess = "true"))
	int32 PlayerScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Information", meta = (AllowPrivateAccess = "true"))
	int32 TimeLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Information", meta = (AllowPrivateAccess = "true"))
	int32 MaxTime;

	//Reference to HUD class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UTimerWidget> HUDClass;

	//Reference to MainMenu class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMainMenuWidget> MainMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UEndGameWidget> EndGameClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UScoreWidget> ScoreClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPlayerHUDWidget> CrosshairClass;

	//Reference for HUD instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	class UTimerWidget* HUDInstance;

	//Reference for Main Menu instace
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	class UMainMenuWidget* MainMenuInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	class UScoreWidget* ScoreInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	class UPlayerHUDWidget* CrosshairInstance;

	UPROPERTY()
	APlayerController* PlayerController;
};
