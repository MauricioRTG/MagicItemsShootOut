// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class TARGETSHOOTINGGAME_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void UpdateHealth(float Amount);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	int32 ScoreAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TargetMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	bool isStaticTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATargetManager> TargetManagerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target Information", meta = (AllowPrivateAccess = "true"))
	class ATargetManager* TargetManager;
};
