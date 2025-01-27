#include "CardGrid.h"
#include "CommandManager.h"
#include "MemoryPuzzleGameMode.h"
#include "Components/GridSlot.h"

UCardGrid::UCardGrid()
{

}

void UCardGrid::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    if (CardButtons.Num() == 0)
    {
        InitializeGrid();
    }
}

void UCardGrid::InitializeGrid()
{
    CardButtons.SetNum(64);

    TArray<UTexture2D*> Textures;

    for (int i = 0; i < 16; i++)
    {
        FString TexturePath = FString::Printf(TEXT("Texture2D'/Game/MemoryPuzzle/Textures/Texture%d.Texture%d'"), i, i);
        UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *TexturePath);
        Textures.Add(Texture);
    }

    TArray<UTexture2D*> ShuffledTextures;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ShuffledTextures.Add(Textures[i]);
        }
    }

    const int32 ArraySize = ShuffledTextures.Num();
    for (int32 i = ArraySize - 1; i > 0; --i)
    {
        const int32 j = FMath::RandRange(0, i);
        ShuffledTextures.Swap(i, j);
    }


    for (int32 Row = 0; Row < 8; Row++)
    {
        for (int32 Col = 0; Col < 8; Col++)
        {
            UCard* Card = NewObject<UCard>(this, UCard::StaticClass());
            if (!Card) continue;

            Card->SetCardIndex(Row * 8 + Col);
            Card->InitializeCard(ShuffledTextures[Row * 8 + Col]);

            AddChild(Card);

            UGridSlot* GridSlot = Cast<UGridSlot>(Card->Slot);
            if (GridSlot)
            {
                GridSlot->SetRow(Row);
                GridSlot->SetColumn(Col);
                GridSlot->SetPadding(FMargin(2.0f));
            }

            CardButtons[Row * 8 + Col] = Card;
        }
    }

    AMemoryPuzzleGameMode* GM = Cast<AMemoryPuzzleGameMode>(GetWorld()->GetAuthGameMode());
    if (GM)
    {
        GM->GetCommandManager()->CardGrid = this;
    }

}
