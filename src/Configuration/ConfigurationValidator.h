#pragma once

#include <memory>

#include "Configuration.h"
#include "Components/ConsoleLogger.h"

namespace NppJavaPlugin {

	class ConfigurationValidator {
	private:
		std::shared_ptr<ConsoleLogger> consoleLogger;

		bool ValidateJavaHome(std::shared_ptr<Configuration> configuration);
		bool ValidateJavacPath(std::shared_ptr<Configuration> configuration);
		bool ValidateJavaPath(std::shared_ptr<Configuration> configuration);
	public:
		ConfigurationValidator(std::shared_ptr<ConsoleLogger> consoleLogger) : consoleLogger(consoleLogger) {}

		bool Validate(std::shared_ptr<Configuration> configuration);
	};
}
