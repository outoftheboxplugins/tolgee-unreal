// Copyright (c) Tolgee. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FTolgeeEditorModule : public IModuleInterface
{
private:
	// Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface interface
};
