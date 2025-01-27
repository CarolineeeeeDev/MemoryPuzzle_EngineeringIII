// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommandManager.h"
#include "GameFramework/GameModeBase.h"
#include "MemoryPuzzleGameMode.generated.h"

UCLASS(minimalapi)
class AMemoryPuzzleGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UCommandManager* CommandManager;

public:
	AMemoryPuzzleGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void WinGame();

	UFUNCTION(BlueprintCallable)
	UCommandManager* GetCommandManager();
};



