#pragma once

#include <windows.h>
#include <memory>

#include "PluginInfrastructure/NppPlugin.h"
#include "PluginInfrastructure/DockingFeature/Docking.h"
#include "PluginInfrastructure/DockingFeature/DockingDlgInterface.h"

#include "NppJavaPluginResources.h"
#include "ConsoleLogger.h"
#include "CRichEdit.h"
#include "NppGateway.h"

namespace NppJavaPlugin {

	class JavaConsole : public DockingDlgInterface, public ConsoleLogger
	{
	private:
		HANDLE hModule;
		HWND hRichEdit;

		std::shared_ptr<NppGateway> nppGateway;

		std::shared_ptr<CRichEdit> richEdit;

		void setParent(HWND parent);

		void InitializeDialog(NppData nppData);
		void InitializeResources();
		void InitializeDependencies();

		void ShowIfHidden();

		INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
		void OnSize(HWND hDlg);
	public:
		JavaConsole(HANDLE hModule, std::shared_ptr<NppGateway> nppGateway) :
			DockingDlgInterface(IDD_DIALOG_CONSOLE),
			hModule(hModule),
			nppGateway(nppGateway) {}

		void display(bool toShow = true) const;

		void Initialize(NppData nppData);

		void Info(LPCTSTR message);
		void Success(LPCTSTR message);
		void Warning(LPCTSTR message);
		void Error(LPCTSTR message);
		void Raw(LPTSTR message);

		void Clear();
	};
}
