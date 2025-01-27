#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Card.generated.h"

class UCommandManager;

UCLASS()
class MEMORYPUZZLE_API UCard : public UButton
{
	GENERATED_BODY()

private:
    UPROPERTY()
    UImage* CardImage;

    UPROPERTY()
    UTexture2D* CardTexture;

    UPROPERTY()
    UCommandManager* CommandManager;

    int32 CardIndex;
    bool bIsRevealed;

public:
    UCard();
    int32 FlippedBackTimes;

    void SetCardIndex(int32 Index) { CardIndex = Index; }
    int32 GetCardIndex() const { return CardIndex; }
    UTexture2D* GetCardTexture() const { return CardTexture; }
    bool GetCardRevealed() const { return bIsRevealed;  }

    UFUNCTION()
    void OnCardClicked();

    void InitializeCard(UTexture2D* NewTexture);

    void SetCardRevealed();
    void SetCardNotRevealed();
};
