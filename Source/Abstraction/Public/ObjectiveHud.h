#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveHud.generated.h"

class UTextBlock;

UCLASS()
class ABSTRACTION_API UObjectiveHud : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateObjectiveText(uint32 ObjectivesCompleted, uint32 TotalObjectives);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ObjectivesText;

};
