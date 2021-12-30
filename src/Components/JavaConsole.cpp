#include "JavaConsole.h"
#include "NppJavaPluginResources.h"

namespace NppJavaPlugin {

	void JavaConsole::Initialize(NppData nppData) {
		InitializeDialog(nppData);
		InitializeResources();
		InitializeDependencies();
	}

	void JavaConsole::InitializeDialog(NppData nppData)
	{
		init((HINSTANCE)hModule, NULL);
		setParent(nppData._nppHandle);
		tTbData	data = { 0 };

		if (!isCreated())
		{
			create(&data);

			data.uMask = DWS_DF_CONT_BOTTOM;
			data.pszName = _T("Java Console");
			data.pszModuleName = getPluginFileName();
			data.dlgID = IDD_DIALOG_CONSOLE;
			::SendMessage(nppData._nppHandle, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&data);
		}
	}

	void JavaConsole::InitializeResources()
	{
		hRichEdit = ::GetDlgItem(_hSelf, IDC_CONSOLE_RICHED);
	}

	void JavaConsole::InitializeDependencies()
	{
		richEdit = std::make_shared<CRichEdit>(hRichEdit);
		richEdit->Initialize();

		display(false);
	}

	void JavaConsole::ShowIfHidden() {
		if (!isVisible())
			display(true);
	}

	void JavaConsole::display(bool toShow) const {
		DockingDlgInterface::display(toShow);

		nppGateway->SetFocusOnScintilla();
	}

	void JavaConsole::setParent(HWND parent) {
		_hParent = parent;
	};

	INT_PTR CALLBACK JavaConsole::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		INT_PTR handleResult = DockingDlgInterface::run_dlgProc(message, wParam, lParam);

		switch (message)
		{
		case WM_NOTIFY:
		case WM_SIZE:
			OnSize(_hSelf);
			return TRUE;
		default:
			return handleResult;
		}
	}

	void JavaConsole::OnSize(HWND hDlg) {
		RECT rect;
		GetClientRect(hDlg, &rect);

		MoveWindow(hRichEdit, rect.left, rect.top, rect.right, rect.bottom, TRUE);
		InvalidateRect(hRichEdit, NULL, TRUE);
		UpdateWindow(hRichEdit);
	}

	void JavaConsole::Info(LPCTSTR message) {
		ShowIfHidden();
		std::wstring line = std::wstring().append(_T(">>> INFO: ")).append(message);

		richEdit->AddLine(line.c_str(), rgbBlack);
	}

	void JavaConsole::Success(LPCTSTR message) {
		ShowIfHidden();
		std::wstring line = std::wstring().append(_T(">>> SUCCESS: ")).append(message);

		richEdit->AddLine(line.c_str(), rgbGreen);
	}

	void JavaConsole::Warning(LPCTSTR message) {
		ShowIfHidden();
		std::wstring line = std::wstring().append(_T(">>> WARNING: ")).append(message);

		richEdit->AddLine(line.c_str(), rgbYellow);
	}

	void JavaConsole::Error(LPCTSTR message) {
		ShowIfHidden();
		std::wstring line = std::wstring().append(_T(">>> ERROR: ")).append(message);

		richEdit->AddLine(line.c_str(), rgbRed);
	}

	void JavaConsole::Raw(LPTSTR message) {
		ShowIfHidden();

		richEdit->AddString(message, rgbBlack);
	}

	void JavaConsole::Clear() {
		ShowIfHidden();

		richEdit->Clear();
	}
}
