#pragma once

#include <windows.h>
#include <string>

namespace NppJavaPlugin {

	constexpr COLORREF rgbBlack = 0x00000000;
	constexpr COLORREF rgbGreen = 0x00008000;
	constexpr COLORREF rgbRed = 0x000000FF;
	constexpr COLORREF rgbYellow = 0x000080FF;

	class CRichEdit
	{
	private:
		HWND hRichEdit;

		void SetDefaultFont();
		void SetCharColor(COLORREF color);
		void SetSel(int start, int stop);
	public:
		CRichEdit(HWND hRichEdit) : hRichEdit(hRichEdit) {}

		void Initialize();

		void AddLine(LPCTSTR line, COLORREF color);
		void AddString(LPTSTR line, COLORREF color);
		void Clear();
	};
}
