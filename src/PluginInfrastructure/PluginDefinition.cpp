//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "NppPlugin.h"

//
// The plugin data that Notepad++ needs
//
FuncItem* funcItem;
size_t funcItemSize;
NppData nppData;

std::shared_ptr<NppPlugin> nppPlugin;

const TCHAR* getPluginName()
{
	return nppPlugin->getName();
}

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginCreate(HANDLE hModule)
{
	nppPlugin = createPlugin(hModule);

	funcItemSize = nppPlugin->getNumberOfActions();
	funcItem = new FuncItem[funcItemSize];
	ZeroMemory(funcItem, sizeof(FuncItem) * funcItemSize);
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginDestroy()
{
	destroyPlugin();

	nppPlugin.reset();
	delete[] funcItem;
}

void pluginInit(NppData pNppData) {
	nppData = pNppData;

	nppPlugin->Initialize(pNppData);
}

//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR* cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey* sk, bool check0nInit)
{
	if (index >= funcItemSize)
		return false;

	if (!pFunc)
		return false;

	lstrcpy(funcItem[index]._itemName, cmdName);
	funcItem[index]._pFunc = pFunc;
	funcItem[index]._init2Check = check0nInit;
	funcItem[index]._pShKey = sk;

	return true;
}
