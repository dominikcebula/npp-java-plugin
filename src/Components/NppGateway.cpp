#include "NppGateway.h"

namespace NppJavaPlugin {

	void NppGateway::Initialize(NppData pNppData)
	{
		nppData = pNppData;
	}

	DocumentInfo NppGateway::GetCurrentDocumentInfo()
	{
		DocumentInfo documentInfo;

		documentInfo.currentPath = GetCurrentDocumentInfoAttribute(NPPM_GETFULLCURRENTPATH);
		documentInfo.fileName = GetCurrentDocumentInfoAttribute(NPPM_GETFILENAME);
		documentInfo.currentDirectory = GetCurrentDocumentInfoAttribute(NPPM_GETCURRENTDIRECTORY);

		return documentInfo;
	}

	std::wstring NppGateway::GetCurrentDocumentInfoAttribute(int attributeType)
	{
		TCHAR attributeValue[MAX_PATH];
		ZeroMemory(attributeValue, MAX_PATH);

		SendMessage(nppData._nppHandle, attributeType, 0, (LPARAM)attributeValue);

		return std::wstring(attributeValue);
	}

	void NppGateway::SaveCurrentFile() {
		SendMessage(nppData._nppHandle, NPPM_SAVECURRENTFILE, 0, 0);
	}

	void NppGateway::SetFocusOnScintilla() {
		int currentScintillaId;
		SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&currentScintillaId);

		if (currentScintillaId == 0)
			SetFocus(nppData._scintillaMainHandle);
		else
			SetFocus(nppData._scintillaSecondHandle);
	}
}
