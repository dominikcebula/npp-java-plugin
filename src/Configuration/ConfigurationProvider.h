#pragma once

#include <memory>

#include "Configuration.h"

namespace NppJavaPlugin {

	class ConfigurationProvider {
	private:
		std::shared_ptr<Configuration> configuration;
	public:
		ConfigurationProvider() : configuration(std::make_shared<Configuration>()) {}

		std::shared_ptr<Configuration> getConfiguration();
	};
}
