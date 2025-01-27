#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "CardGrid.h"
#include "UObject/NoExportTypes.h"
#include "CommandManager.generated.h"

class UCard;

UCLASS()
class MEMORYPUZZLE_API UCommandManager : public UObject
{
    GENERATED_BODY()

private:
    int32 CurrentIndex; //index of command
    bool bIsFlipping;

    UPROPERTY()
    TArray<UCommand*> CommandHistory; //save commands here

    UPROPERTY()
    UCard* FirstCard;

    UPROPERTY()
    UCard* SecondCard;

    

public:
    UCommandManager();

    UPROPERTY()
    UCardGrid* CardGrid;

    UPROPERTY()
    TArray<UCard*> FlippedCards;

    void ExecuteCommand(UCommand* Command);

    UFUNCTION(BlueprintCallable)
    void Undo();

    UFUNCTION(BlueprintCallable)
    void Redo();

   
    

    bool GetIsFlipping() const { return bIsFlipping; }
    int32 GetCurrentIndex() const { return CurrentIndex; }
    void AddCurrentIndex() { CurrentIndex++; }
    void MinusCurrentIndex() { CurrentIndex--;  }

    void OnCardFlipped(UCard* Card);

};
