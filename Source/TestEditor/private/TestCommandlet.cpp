#include "TestCommandlet.h"
#include "Misc/CommandLine.h"
#include "Misc/OutputDevice.h"
#include "Misc/Paths.h"
#include "Misc/MessageDialog.h"
#include "HAL/PlatformProcess.h"

int32 UTestCommandlet::Main(const FString &Params)
{
    TArray<FString> Tokens, Switches;
    FCommandLine::Parse(FCommandLine::Get(), Tokens, Switches);

    FString DialogText;
    DialogText += TEXT("=== Commandlet Input Summary ===\n\n");
    DialogText += FString::Printf(TEXT("Params:\n%s\n\n"), *Params);
    DialogText += FString::Printf(TEXT("Full CommandLine:\n%s\n"), FCommandLine::Get());
    DialogText += TEXT("\n-- Tokens --\n");
    for (int32 i = 0; i < Tokens.Num(); ++i)
        DialogText += FString::Printf(TEXT("[%d] %s\n"), i, *Tokens[i]);
    DialogText += TEXT("\n-- Switches --\n");
    for (int32 i = 0; i < Switches.Num(); ++i)
        DialogText += FString::Printf(TEXT("[%d] -%s\n"), i, *Switches[i]);
    const FText TitleText = FText::FromString(TEXT("Commandlet Parameters"));

    FMessageDialog::Open(
        EAppMsgType::Ok,
        FText::FromString(DialogText),
        &TitleText);

    return 0;
}
