#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AActor;
class UCapsuleComponent;
class UPrimitiveComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionSuccess);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABSTRACTION_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	//this is broadcasted from children, they know when an interaction has successfully finished
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionSuccess InteractionSuccess;

	UCapsuleComponent* GetTriggerCapsule() const { return TriggerCapsule; }
protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {};

	UFUNCTION(BlueprintCallable)
	virtual void InteractionRequested() {};

	UPROPERTY(EditAnywhere)
	FText InteractionPrompt;

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule = nullptr;

	AActor* InteractingActor = nullptr;
	bool bActive = true;
	FDelegateHandle InteractionBinding;
};