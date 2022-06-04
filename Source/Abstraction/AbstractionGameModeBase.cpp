// Copyright Epic Games, Inc. All Rights Reserved.


#include "AbstractionGameModeBase.h"
#include "ObjectiveWorldSubSystem.h"

void AAbstractionGameModeBase::StartPlay()
{
	Super::StartPlay();
	UObjectiveWorldSubSystem* ObjectiveWorldSubSystem = GetWorld()->GetSubsystem<UObjectiveWorldSubSystem>();
	if (ObjectiveWorldSubSystem)
	{
		ObjectiveWorldSubSystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubSystem->DisplayObjectiveWidget();
	}
}