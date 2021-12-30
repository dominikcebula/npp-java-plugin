#include "CRichEdit.h"
#include "RichEdit.h"
#include <tchar.h>
#include "Utils.h"

namespace NppJavaPlugin {

	void CRichEdit::Initialize() {
		SetDefaultFont();
	}

	void CRichEdit::SetDefaultFont()
	{
		CHARFORMAT charFormat;

		charFormat.cbSize = sizeof(CHARFORMAT);
		charFormat.dwMask = CFM_SIZE | CFM_FACE;
		lstrcpyn(charFormat.szFaceName, _T("Courier New"), LF_FACESIZE);
		charFormat.yHeight = PixelsToTwips(hRichEdit, 13);
		charFormat.bPitchAndFamily = 1;
		charFormat.dwEffects = 0;

		SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&charFormat);
	}

	void CRichEdit::AddLine(LPCTSTR line, COLORREF color)
	{
		AddString((LPTSTR)line, color);
		AddString(_T("\r\n"), color);
	}

	void CRichEdit::AddString(LPTSTR line, COLORREF color)
	{
		SetSel(-1, -1);
		SetCharColor(color);

		SendMessage(hRichEdit, EM_REPLACESEL, FALSE, (LPARAM)line);

		SendMessage(hRichEdit, WM_VSCROLL, SB_PAGEDOWN, NULL);
		SendMessage(hRichEdit, WM_VSCROLL, SB_PAGEDOWN, NULL);
	}

	void CRichEdit::Clear() {
		SendMessage(hRichEdit, WM_SETTEXT, 0, (LPARAM)_T(""));
	}

	void CRichEdit::SetSel(int start, int stop)
	{
		CHARRANGE charRange;
		charRange.cpMin = start;
		charRange.cpMax = stop;
		SendMessage(hRichEdit, EM_EXSETSEL, 0, (LPARAM)&charRange);
	}

	void CRichEdit::SetCharColor(COLORREF color)
	{
		CHARFORMAT charFormat;

		ZeroMemory(&charFormat, sizeof(CHARFORMAT));
		charFormat.cbSize = sizeof(CHARFORMAT);
		charFormat.dwMask = CFM_COLOR;
		charFormat.crTextColor = color;

		SendMessage(hRichEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&charFormat);
	}
}
