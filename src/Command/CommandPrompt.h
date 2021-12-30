#pragma once

#include "Components/ConsoleLogger.h"
#include "Command.h"

namespace NppJavaPlugin {

	class CommandPrompt
	{
	private:
		std::shared_ptr<ConsoleLogger> consoleLogger;
	public:
		CommandPrompt(std::shared_ptr<ConsoleLogger> consoleLogger) : consoleLogger(consoleLogger) {}

		bool Execute(CommandInfo commandInfo);
	};
}
