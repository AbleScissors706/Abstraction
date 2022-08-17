#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.generated.h"

class UObjectiveComponent;
class UObjectiveHud;
class UUserWidget;

UCLASS()
class ABSTRACTION_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UObjectiveWorldSubsystem() {}

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);
	
	//we call this from maps that we want to display objectives(ie main menu will not call this function)
	UFUNCTION(BlueprintCallable)
	void OnMapStart();

	/*UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription() { return TEXT("Open Door"); }*/

	/*void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveClass);
	void DisplayObjectiveWidget();

	void OnObjectiveCompleted();*/

protected:

	virtual void Deinitialize() override;

	void CreateObjectiveWidget();
	
	void DisplayObjectiveWidget();
	void RemoveObjectiveWidget();

	void DisplayObjectivesCompleteWidget();
	void RemoveObjectivesCompleteWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(const UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);

private:	

	//UUserWidget* ObjectiveWidget = nullptr;

	UPROPERTY()
	UObjectiveHud* ObjectiveWidget = nullptr;

	UPROPERTY()
	UUserWidget* ObjectivesCompleteWidget = nullptr;

	TArray<const UObjectiveComponent*> Objectives;
};