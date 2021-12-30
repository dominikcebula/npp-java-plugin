#include <tchar.h>

#include "ConfigurationValidator.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	bool ConfigurationValidator::Validate(std::shared_ptr<Configuration> configuration) {
		return ValidateJavaHome(configuration)
			&& ValidateJavacPath(configuration)
			&& ValidateJavaPath(configuration);
	}

	bool ConfigurationValidator::ValidateJavaHome(std::shared_ptr<Configuration> configuration) {
		std::wstring javaHome = configuration->getJavaHome();

		if (javaHome.empty()) {
			consoleLogger->Error(std::wstring().append(std::wstring(JAVA_HOME)).append(_T(" property is empty")).c_str());
			return false;
		}

		if (!fileExists(javaHome)) {
			consoleLogger->Error(std::wstring().append(std::wstring(JAVA_HOME))
				.append(_T(" property points to non-existing directory \"")).append(javaHome).append(_T("\"")).c_str());
			return false;
		}

		std::wstring javaHomeBin = javaHome;
		javaHomeBin.append(_T("\\bin"));

		if (!fileExists(javaHomeBin)) {
			consoleLogger->Error(std::wstring().append(std::wstring(JAVA_HOME))
				.append(_T(" property points to directory that does not contain \"bin\" folder under location \"")).append(javaHome).append(_T("\"")).c_str());
			return false;
		}

		return true;
	}

	bool ConfigurationValidator::ValidateJavacPath(std::shared_ptr<Configuration> configuration) {
		std::wstring javacPath = configuration->getJavacPath();

		if (!fileExists(javacPath)) {
			consoleLogger->Error(std::wstring().append(_T("Expected Java Compiler \""))
				.append(JAVAC_EXECUTABLE_NAME).append(_T("\" to exist under \"")).append(javacPath).append(_T("\"")).c_str());
			return false;
		}

		return true;
	}

	bool ConfigurationValidator::ValidateJavaPath(std::shared_ptr<Configuration> configuration) {
		std::wstring javaPath = configuration->getJavaPath();

		if (!fileExists(javaPath)) {
			consoleLogger->Error(std::wstring().append(_T("Expected Java Executable \""))
				.append(JAVA_EXECUTABLE_NAME).append(_T("\" to exist under \"")).append(javaPath).append(_T("\"")).c_str());
			return false;
		}

		return true;
	}
}
