#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.generated.h"

UCLASS(Abstract)
class MEMORYPUZZLE_API UCommand : public UObject
{
    GENERATED_BODY()

public:
    virtual void Execute() PURE_VIRTUAL(UCommand::Execute, );
    virtual void Undo() PURE_VIRTUAL(UCommand::Undo, );
    virtual void Redo() PURE_VIRTUAL(UCommand::Redo, );
};