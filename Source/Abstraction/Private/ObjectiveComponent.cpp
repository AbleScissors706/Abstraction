#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.h"
#include "Engine/World.h"

UObjectiveComponent::UObjectiveComponent()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;
}

void UObjectiveComponent::SetState(EObjectiveState NewState)
{
	if (NewState != State)
	{
		State = NewState;
		OnStateChanged.Broadcast(this, NewState);
	}
}


void UObjectiveComponent::InitializeComponent()
{
	Super::InitializeComponent();
	//register
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
	}
}

void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}