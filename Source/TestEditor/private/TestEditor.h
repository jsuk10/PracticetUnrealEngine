#pragma once

#include "Modules/ModuleManager.h"

class FTestEditor : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
