#pragma once

#include <string>

#include "PluginInfrastructure/DockingFeature/StaticDialog.h"
#include "PluginInfrastructure/PluginInterface.h"

namespace NppJavaPlugin {

	class AboutDialog : public StaticDialog
	{
	private:
		HANDLE hModule;

		void InitializeDialog(NppData nppData);
		void InitializePluginVersion();
		void setParent(HWND parent);

		std::wstring GetPluginVersion();

		INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	public:
		AboutDialog(HANDLE hModule) : hModule(hModule) {}

		void Initialize(NppData nppData);

		void display(bool toShow);
	};
}
