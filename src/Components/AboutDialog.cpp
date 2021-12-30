#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>

#include "AboutDialog.h"
#include "NppJavaPluginResources.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	void AboutDialog::Initialize(NppData nppData) {
		InitializeDialog(nppData);
		InitializePluginVersion();
	}

	void AboutDialog::InitializeDialog(NppData nppData) {
		init((HINSTANCE)hModule, NULL);
		setParent(nppData._nppHandle);

		create(IDD_DIALOG_ABOUT);
	}

	void AboutDialog::InitializePluginVersion() {
		Static_SetText(GetDlgItem(_hSelf, IDC_STATIC_VERSION), GetPluginVersion().c_str());
	}

	std::wstring AboutDialog::GetPluginVersion() {
		return getPluginVersion(hModule);
	}

	void AboutDialog::setParent(HWND parent) {
		_hParent = parent;
	};

	void AboutDialog::display(bool toShow) {
		if (toShow)
			goToCenter();

		StaticDialog::display(toShow);
	}

	INT_PTR CALLBACK AboutDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
		case WM_NOTIFY: {
			switch (reinterpret_cast<LPNMHDR>(lParam)->code) {
			case NM_CLICK:
			case NM_RETURN: {
				PNMLINK nmLink = reinterpret_cast<PNMLINK>(lParam);
				LITEM linkItem = nmLink->item;

				ShellExecute(nullptr, L"open", linkItem.szUrl, nullptr, nullptr, SW_SHOW);

				return TRUE;
			}
			}
			return FALSE;
		}
		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
			case IDOK:
				if (HIWORD(wParam) == BN_CLICKED) {
					display(false);
					return TRUE;
				}
			}
			return FALSE;
		}
		case WM_CLOSE: {
			display(false);
			return TRUE;
		}
		default:
			return FALSE;
		}
	}
}
