#pragma once

#include "Modules/ModuleManager.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

class FTestEditor : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void AddMenuBarEntry(FMenuBarBuilder& MenuBarBuilder);
    void FillPulldownMenu(FMenuBuilder& MenuBuilder);
    void AddToolbarButton(FToolBarBuilder& ToolbarBuilder);
    void OnClickMenuFun();
    void OpenAssetPickerWindow();

    TSharedPtr<class SWindow> PickerWindow;
};
