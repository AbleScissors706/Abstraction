// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubSystem.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWorldSubSystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWigetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}

}

void UObjectiveWorldSubSystem::DisplayObjectiveWidget()
{
	ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubSystem::DisplayObjectiveWidget ObjectiveWidget is nullptr"));
	ObjectiveWidget->AddToViewport();
}
