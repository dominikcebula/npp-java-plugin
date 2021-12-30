#pragma once

#include <string>
#include <tchar.h>

namespace NppJavaPlugin {

	constexpr const wchar_t* JAVA_HOME = _T("JAVA_HOME");
	constexpr const wchar_t* JAVAC_EXECUTABLE_NAME = _T("javac.exe");
	constexpr const wchar_t* JAVA_EXECUTABLE_NAME = _T("java.exe");

	class Configuration
	{
	public:
		std::wstring getJavaHome();
		std::wstring getJavacPath();
		std::wstring getJavaPath();
	};
}
