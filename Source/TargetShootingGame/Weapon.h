// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class TARGETSHOOTINGGAME_API UWeapon : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	/*Enhanced Input*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/*Function triggered when player fires weapon*/
	UFUNCTION()
	void OnFire();

	/*Projectile class to spawn it when weapon is fired*/
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	/*Muzzle offset where the projectiles will spawn from weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay, meta = (AllowPrivateAccess = "true"))
	FVector MuzzleOffset;

	/*Constructor*/
	UWeapon();

private:
	/*Character holding the weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	class APlayerCharacter* PlayerCharacter;
};
