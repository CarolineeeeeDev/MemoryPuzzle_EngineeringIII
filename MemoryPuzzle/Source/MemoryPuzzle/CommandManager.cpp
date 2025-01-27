#include "CommandManager.h"
#include "FlipCardCommand.h"
#include "MemoryPuzzleGameMode.h"
#include "Card.h"

UCommandManager::UCommandManager()
{
    CurrentIndex = -1;
    bIsFlipping = false;
}

void UCommandManager::ExecuteCommand(UCommand* Command)
{
    if (!Command)
    {
        return;
    }

    Command->Execute();

    if (CurrentIndex < CommandHistory.Num() - 1)
    {
        CommandHistory.SetNum(CurrentIndex + 1);
    }
    CommandHistory.Add(Command);
    CurrentIndex++;
}

void UCommandManager::Undo()
{
    if (bIsFlipping) return;

    if (CurrentIndex >= 0)
    {
        CommandHistory[CurrentIndex]->Undo();
        CurrentIndex--;
    }
}

void UCommandManager::Redo()
{
    if (bIsFlipping) return;

    if (CurrentIndex < CommandHistory.Num() - 1)
    {
        CurrentIndex++;
        CommandHistory[CurrentIndex]->Redo();
    }
}

void UCommandManager::OnCardFlipped(UCard* Card)
{
    if (!Card)
    {
        return;
    }

    FlippedCards.Add(Card);

    if (FlippedCards.Num() == 2)
    {
        FirstCard = FlippedCards[0];
        SecondCard = FlippedCards[1];

        if (FirstCard->GetCardTexture() == SecondCard->GetCardTexture())
        {
            FlippedCards.Empty();
            if (CardGrid)
            {
                TArray<UCard*> Cards = CardGrid->CardButtons;
                for (auto SingleCard : Cards)
                {
                    if (!SingleCard->GetCardRevealed()) return;
                }
                AMemoryPuzzleGameMode* GM = Cast<AMemoryPuzzleGameMode>(GetWorld()->GetAuthGameMode());
                if (GM)
                {
                    GM->WinGame();
                }
            }
        }
        else
        {
            bIsFlipping = true;
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    if (FirstCard)
                    {
                        UFlipCardCommand* FlipCmd = NewObject<UFlipCardCommand>(this);
                        FlipCmd->InitializeCommand(FirstCard);
                        CommandHistory.Add(FlipCmd);
                        CurrentIndex++;
                        FirstCard->SetCardNotRevealed();
                    }
                    if (SecondCard)
                    {
                        UFlipCardCommand* FlipCmd = NewObject<UFlipCardCommand>(this);
                        FlipCmd->InitializeCommand(SecondCard);
                        CommandHistory.Add(FlipCmd);
                        CurrentIndex++;
                        SecondCard->SetCardNotRevealed();
                    }
                    FlippedCards.Empty();
                    bIsFlipping = false;
                }, 0.5f, false);
        }
    }
}