#include "FlipCardCommand.h"
#include "MemoryPuzzleGameMode.h"

UFlipCardCommand::UFlipCardCommand()
{
    Card = nullptr;
    bWasRevealed = false;
}

void UFlipCardCommand::InitializeCommand(UCard* InCard)
{
    AMemoryPuzzleGameMode* GM = Cast<AMemoryPuzzleGameMode>(GetWorld()->GetAuthGameMode());
    if (GM)
    {
        CommandManager = GM->GetCommandManager();
    }

    Card = InCard;
    bWasRevealed = Card->GetCardRevealed();
}

void UFlipCardCommand::Execute()
{
    if (CommandManager->GetIsFlipping()) return;

    if (!bWasRevealed)
    {
        Card->SetCardRevealed();
        CommandManager->OnCardFlipped(Card);
    }
}

void UFlipCardCommand::Undo()
{
    if (CommandManager->GetIsFlipping()) return;

    if (!bWasRevealed)
    {
        Card->SetCardNotRevealed();
        CommandManager->FlippedCards.Remove(Card);
    }
    else
    {
        Card->SetCardRevealed();
        CommandManager->FlippedCards.AddUnique(Card);
    }

    if (CommandManager->FlippedCards.Num()==2) //undo again
    {
        if (CommandManager->GetCurrentIndex() > 0)
        {
            CommandManager->MinusCurrentIndex();
            CommandManager->Undo();
            CommandManager->AddCurrentIndex();
        }
    }
}

void UFlipCardCommand::Redo()
{
    Execute();
}
