#pragma once

#include "CoreMinimal.h"
#include "Card.h"
#include "Components/GridPanel.h"
#include "CardGrid.generated.h"

UCLASS()
class MEMORYPUZZLE_API UCardGrid : public UGridPanel
{
	GENERATED_BODY()

public:
    UPROPERTY()
    TArray<UCard*> CardButtons;

    UCardGrid();

    virtual void SynchronizeProperties() override;

private:
    void InitializeGrid();
};
