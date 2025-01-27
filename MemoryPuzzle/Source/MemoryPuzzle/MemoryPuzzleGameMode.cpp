// Copyright Epic Games, Inc. All Rights Reserved.

#include "MemoryPuzzleGameMode.h"
#include "MemoryPuzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMemoryPuzzleGameMode::AMemoryPuzzleGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMemoryPuzzleGameMode::BeginPlay()
{
	Super::BeginPlay();
}

UCommandManager* AMemoryPuzzleGameMode::GetCommandManager()
{
	if (!CommandManager)
	{
		CommandManager = NewObject<UCommandManager>(this);

	}
	return CommandManager;
}
