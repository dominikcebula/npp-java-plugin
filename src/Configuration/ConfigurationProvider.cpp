#include "ConfigurationProvider.h"

namespace NppJavaPlugin {

	std::shared_ptr<Configuration> ConfigurationProvider::getConfiguration() {
		return configuration;
	}
}
