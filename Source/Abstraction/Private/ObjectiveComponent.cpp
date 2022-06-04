// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubSystem.h"

UObjectiveComponent::UObjectiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;
}

void UObjectiveComponent::SetState(EObjectiveState NewState)
{
	if (NewState != State)
	{
		State = NewState;
		StateChangedEvent.Broadcast(this, NewState);
	}
}


void UObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	//register
	UObjectiveWorldSubSystem* ObjectiveWorldSubSystem = GetWorld()->GetSubsystem<UObjectiveWorldSubSystem>();
	if (ObjectiveWorldSubSystem)
	{
		ObjectiveWorldSubSystem->AddObjective(this);
	}
}

void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubSystem* ObjectiveWorldSubSystem = GetWorld()->GetSubsystem<UObjectiveWorldSubSystem>();
	if (ObjectiveWorldSubSystem)
	{
		ObjectiveWorldSubSystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}