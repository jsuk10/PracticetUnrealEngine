#include "TestEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FTestEditor, TestEditor)

void FTestEditor::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("MyCustomModule ���۵�!"));
}

void FTestEditor::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("MyCustomModule �����!"));
}
