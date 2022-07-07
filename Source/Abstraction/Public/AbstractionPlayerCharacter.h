// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbstractionPlayerCharacter.generated.h"

class UHealthComponent;

DECLARE_MULTICAST_DELEGATE(FInteractionStartRequest);
DECLARE_MULTICAST_DELEGATE(FInteractionCancelRequest);

UCLASS()
class ABSTRACTION_API AAbstractionPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:	

	// Sets default values for this character's properties
	//AAbstractionPlayerCharacter();
	// 
	AAbstractionPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);

	FInteractionStartRequest OnInteractionStartRequested;
	FInteractionCancelRequest OnInteractionCancelRequested;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	void InteractionStartRequested();
	void InteractionCancelRequested();

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;
};
