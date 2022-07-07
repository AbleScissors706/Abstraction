// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DealDamageComponent.generated.h"

class UCapsuleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABSTRACTION_API UDealDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDealDamageComponent();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UCapsuleComponent* GetTriggerCapsule() const { return TriggerCapsule; }

	bool IsEnabled() const { return bEnabled; }
	void SetEnabled(bool value) { bEnabled = value; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 50.0f;

	//the base damage is distributed over this time
	UPROPERTY(EditAnywhere)
	float DamageTotalTime = 2.0f;

	//teh time interval at which to apply take damage
	UPROPERTY(EditAnywhere)
	float TakeDamageInterval = 0.5f;

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule;

	bool bEnabled = true;
};