// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshWeapon.h"
#include "Projectile.h"
#include "PlayerCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UStaticMeshWeapon::UStaticMeshWeapon()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UStaticMeshWeapon::BeginPlay()
{
	/*Get Character*/
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		/*Get Controller*/
		if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
		{
			/*Add mapping Context*/
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(FireMappingContext, 1);
			}

			/*Set up ActionBIndings*/
			if (UEnhancedInputComponent* InputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				InputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UStaticMeshWeapon::OnFire);
			}
		}
	}
}

void UStaticMeshWeapon::OnFire()
{
	/* Check if the PlayerCharacter and Controller exists*/
	if (PlayerCharacter == nullptr || PlayerCharacter->GetController() == nullptr)
	{
		return;
	}
	/*Checks if the ProjectileClass exists*/
	if (ProjectileClass)
	{
		/*Check if world exists*/
		UWorld* const World = GetWorld();
		if (World)
		{
			/*Get Player Controller*/
			APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
			/*Obtain Rotation with the PlayerController's PlayerManagerCamera*/
			FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			/*Obtain Location (we add the origin position of weapon with the MuzzleOffset [Rotated to match the camera rotation]*/
			FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			/*Spawn projectile*/
			World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}
}
