// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Target.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileDamage = -50.0f;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));

	/*Set the root component to the collision component*/
	RootComponent = ProjectileMesh;

	//Use ProjectileMovementCompoment to dictate the movement of the projectile*/
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	//The collisionComponent is the component that will be moved by the ProjectileMovementComponent*/
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	//Set projectile speed*/
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f; 
	//This projectile will have its rotation updated each frame to match the direction of its velocity.*/
	ProjectileMovement->bRotationFollowsVelocity = true;
	//Simple bounces will be simulated*/
	ProjectileMovement->bShouldBounce = true;


	//Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*Bind onHit function to the OnComponentHit delagate*/
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATarget* Target = Cast<ATarget>(OtherActor);
	if (Target)
	{
		UE_LOG(LogTemp, Log, TEXT("Projectile hit other actor"));
	}
}

