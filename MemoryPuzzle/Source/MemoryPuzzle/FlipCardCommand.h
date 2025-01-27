#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "Card.h"
#include "FlipCardCommand.generated.h"

UCLASS()
class MEMORYPUZZLE_API UFlipCardCommand : public UCommand
{
    GENERATED_BODY()

public:
    UPROPERTY()
    UCard* Card;

    UPROPERTY()
    UCommandManager* CommandManager;

    UFlipCardCommand();

    void InitializeCommand(UCard* InCard);
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();

    bool GetWasRevealed() const { return bWasRevealed; }

private:
    bool bWasRevealed;
};


