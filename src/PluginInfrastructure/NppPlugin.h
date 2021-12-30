#pragma once

#include <memory>

#include "PluginInterface.h"
#include "PluginDefinition.h"
#include "menuCmdID.h"

class NppPlugin
{
public:
	virtual ~NppPlugin() {}

	virtual const TCHAR* getName() = 0;
	virtual const size_t getNumberOfActions() = 0;

	virtual void Initialize(NppData nppData) = 0;
};

std::shared_ptr<NppPlugin> createPlugin(HANDLE hModule);
void destroyPlugin();
