// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "TargetManager.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = TargetMeshComponent;

	MaxHealth = 100.0f;
	Health = MaxHealth;
	ScoreAmount = 10;

	TargetManagerClass = ATargetManager::StaticClass();
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	TargetMeshComponent->OnComponentHit.AddDynamic(this, &ATarget::OnHit);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::UpdateHealth(float Amount)
{
	/*Update health with the amount provided, and clamp it between 0 and MaxHealth*/
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
}

void ATarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);

	if (Projectile)
	{
		UE_LOG(LogTemp, Log, TEXT("Target hit"));
		//Decrease target's health on hit
		UpdateHealth(Projectile->ProjectileDamage);
		if (Health <= 0)
		{
			//Update player score
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			PlayerCharacter->UpdateScore(ScoreAmount);

			//Get reference to TargetManager
			TargetManager = Cast<ATargetManager>(UGameplayStatics::GetActorOfClass(GetWorld(), TargetManagerClass));
			//Empties TargetManager arrays and initialize availale targets again, finding all targets in scene
			if (TargetManager)
			{
				TargetManager->RemoveActiveTarget(this);
				//TargetManager->RemoveAvailableTarget(this);
			}

			//Destroy if target's health reaches 0
			//Destroy();
			//Hide Target
			SetActorHiddenInGame(true);

			//Disable collision, to avoid collision when hidden
			SetActorEnableCollision(false);
		}
	}
}

