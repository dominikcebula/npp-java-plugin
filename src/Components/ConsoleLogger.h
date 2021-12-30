#pragma once

#include <Windows.h>
#include <string>

namespace NppJavaPlugin {

	class ConsoleLogger
	{
	public:
		virtual void Info(LPCTSTR message) = 0;
		virtual void Success(LPCTSTR message) = 0;
		virtual void Warning(LPCTSTR message) = 0;
		virtual void Error(LPCTSTR message) = 0;
		virtual void Raw(LPTSTR message) = 0;
	};
}
