#pragma once

#include <windows.h>
#include <string>

namespace NppJavaPlugin {

	std::wstring GetLastErrorAsString();
	int PixelsToTwips(HWND hWnd, int nPixels);
	TCHAR* wstringAsTChar(std::wstring str);
	std::string wstringAsString(std::wstring str);
	std::wstring getEnvVariableValue(std::wstring variableName);
	std::wstring replaceExtension(std::wstring fileName, std::wstring targetExtension);
	std::wstring removeExtension(std::wstring fileName);
	bool hasFileExtension(std::wstring fileName, std::wstring expectedExtension);
	std::wstring getFileExtension(std::wstring fileName);
	bool fileExists(std::wstring filePath);
	std::wstring getPluginVersion(HANDLE hModule);
}
