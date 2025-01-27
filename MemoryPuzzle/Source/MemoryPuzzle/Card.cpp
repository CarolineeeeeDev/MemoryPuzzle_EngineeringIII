#include "Card.h"
#include "CommandManager.h"
#include "Components/ButtonSlot.h"
#include "MemoryPuzzleGameMode.h"
#include "FlipCardCommand.h"

UCard::UCard()
{
    OnClicked.AddDynamic(this, &UCard::OnCardClicked);
}

void UCard::InitializeCard(UTexture2D* NewTexture)
{
    AMemoryPuzzleGameMode* GM = Cast<AMemoryPuzzleGameMode>(GetWorld()->GetAuthGameMode());
    if (GM)
    {
        CommandManager = GM->GetCommandManager();
    }

    bIsRevealed = false;
    FlippedBackTimes = 0;

    CardImage = NewObject<UImage>(this, UImage::StaticClass());
    
    if (CardImage)
    {
        CardImage->SetBrushFromTexture(nullptr);
        CardImage->SetVisibility(ESlateVisibility::Visible);
        AddChild(CardImage);
        UButtonSlot* ButtonSlot = Cast<UButtonSlot>(CardImage->Slot);

        if (ButtonSlot)
        {
            ButtonSlot->SetPadding(FMargin(0.0f));
            ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
            ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
        }
    }
    SetCardNotRevealed();

    if (CardImage && NewTexture)
    {
        CardTexture = NewTexture;
    }
}

void UCard::SetCardRevealed()
{
    bIsRevealed = true;
    CardImage->SetBrushFromTexture(CardTexture);
}

void UCard::SetCardNotRevealed()
{
    bIsRevealed = false;
    UTexture2D* GreyTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/MemoryPuzzle/Textures/NotRevealed.NotRevealed"));
    CardImage->SetBrushFromTexture(GreyTexture);
}

void UCard::OnCardClicked()
{
    if (bIsRevealed) return; //if already revealed, do nothing 
    if (CommandManager)
    {
        if (CommandManager->GetIsFlipping()) return; //if is flipping cards, do nothing 
        UFlipCardCommand* FlipCmd = NewObject<UFlipCardCommand>(this);
        FlipCmd->InitializeCommand(this);
        CommandManager->ExecuteCommand(FlipCmd);
    }
}
