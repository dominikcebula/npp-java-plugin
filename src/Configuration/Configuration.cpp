#include <tchar.h>

#include "Configuration.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	std::wstring Configuration::getJavaHome() {
		return getEnvVariableValue(std::wstring(JAVA_HOME));
	}

	std::wstring Configuration::getJavacPath() {
		return getJavaHome().append(_T("\\bin\\")).append(JAVAC_EXECUTABLE_NAME);
	}

	std::wstring Configuration::getJavaPath() {
		return getJavaHome().append(_T("\\bin\\")).append(JAVA_EXECUTABLE_NAME);
	}
}
