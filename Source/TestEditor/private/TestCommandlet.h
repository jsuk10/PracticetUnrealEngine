#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "TestCommandlet.generated.h"

UCLASS(Config = Editor)
class UTestCommandlet : public UCommandlet
{
    GENERATED_BODY()

public:
    // 커멘드릿 진입점
    virtual int32 Main(const FString &Params) override;
};
