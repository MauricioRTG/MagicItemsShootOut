// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainMenuWidget.h"
#include "TimerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "EndGameWidget.h"
#include "ScoreWidget.h"
#include "PlayerHUDWidget.h"

/*
* Enhanced Input:
* 1. Create UEnhancedInputMappingContext and UEnhancedInputAction variables (they are going to be assigned in editor, so we need to create them in editor first)
* 2. Create function called for a specific action input (eg. void Look(FInputActionValue &Value)
* 3. In BeginPlay() add mapping context, using UEnhancedInputLocalPlayerSubsystem and PlayerController
* 4. Bind functionality to input in SetupPlayerInputComponent with UEnhancedInputComponent
* 5. Implement the function.
*/

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Initialize Capsule Component*/
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	/*Create Camera Controller*/
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(10.0f, 0.0f, 66.0f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Get Controller
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		/*Add mapping context*/
		if (UEnhancedInputLocalPlayerSubsystem* Subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsytem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	//Create widget instance in screen
	ShowMainMenu();
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	//Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		/*Add yaw (rotate in the x-axis) and pitch (rotate in the y-axis)*/
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	/*Set up action binding*/
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
}

void APlayerCharacter::UpdateScore(int &Amount)
{
	PlayerScore += Amount;
	/*If player score decreases less than 0, then set its minimum to 0*/
	if (PlayerScore < 0)
	{
		PlayerScore = 0;
	}
}

void APlayerCharacter::ShowHUD()
{
	//Check if HUD class is set
	if (HUDClass)
	{
		HUDInstance = CreateWidget<UTimerWidget>(GetWorld(), HUDClass);

		//Check if HUD instance is created
		if (HUDInstance)
		{
			HUDInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("HUD Instance not created"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUD Class not set"));
	}
}

void APlayerCharacter::ShowMainMenu()
{
	if (MainMenuClass)
	{
		MainMenuInstance = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuClass);

		if (MainMenuInstance)
		{
			//Add MainMenu widget to viewport
			MainMenuInstance->AddToViewport();

			//Interact only with UI elements only and show cursor
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Main Menu Instance not created"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Main Menu Class not set"));
	}
}

void APlayerCharacter::ShowEndGame()
{
	if (EndGameClass)
	{
		UEndGameWidget* EndGameInstance = CreateWidget<UEndGameWidget>(GetWorld(), EndGameClass);
		if (EndGameInstance)
		{
			//Add EndGame widget to viewport
			EndGameInstance->AddToViewport();

			//Interact only with UI elements and show cursor
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("End Game Instance not created"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("End Game Class not set"));
	}
}

void APlayerCharacter::HideHUD()
{
	if (HUDInstance)
	{
		//Remove widget from viewport and destruct instance
		HUDInstance->RemoveFromParent();
		HUDInstance->Destruct();
	}
}

void APlayerCharacter::ShowScore()
{
	if (ScoreClass)
	{
		ScoreInstance = CreateWidget<UScoreWidget>(GetWorld(), ScoreClass);
		if (ScoreInstance)
		{
			ScoreInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Score Widget Instance not created"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Score Widget Class not set"));
	}
}

void APlayerCharacter::HideScore()
{
	if (ScoreInstance)
	{
		//Remove widget from viewport and destruct instance
		ScoreInstance->RemoveFromParent();
		ScoreInstance->Destruct();
	}
}

void APlayerCharacter::ShowCrosshair()
{
	if (CrosshairClass)
	{
		CrosshairInstance = CreateWidget<UPlayerHUDWidget>(GetWorld(), CrosshairClass);
		if (CrosshairInstance)
		{
			CrosshairInstance->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CrossHair Widget instance not created"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CrossHair Widget Class not set"));
	}
}

void APlayerCharacter::HideCrosshair()
{
	if (CrosshairInstance)
	{
		//Remove widget from viewport and destruct instance
		CrosshairInstance->RemoveFromParent();
		CrosshairInstance->Destruct();
	}
}

