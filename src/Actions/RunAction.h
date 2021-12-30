#pragma once

#include <memory>

#include "PluginInfrastructure/NppPlugin.h"
#include "Components/ConsoleLogger.h"
#include "Command/LoggingCommand.h"
#include "Components/NppGateway.h"
#include "Configuration/ConfigurationProvider.h"
#include "Configuration/ConfigurationValidator.h"
#include "Command/CommandPrompt.h"

namespace NppJavaPlugin {

	class RunAction
	{
	private:
		std::shared_ptr<ConfigurationProvider> configurationProvider;
		std::shared_ptr<ConfigurationValidator> configurationValidator;
		std::shared_ptr<ConsoleLogger> consoleLogger;
		std::shared_ptr<NppGateway> nppGateway;
		std::shared_ptr<CommandPrompt> commandPrompt;

		std::shared_ptr<ShortcutKey> shortcutKey;

		std::wstring BuildRunCommand(DocumentInfo currentDocumentInfo, std::wstring className, std::shared_ptr<Configuration> configuration);
		void InitializeShortcutKey();

		bool Validate(std::shared_ptr<Configuration> configuration, DocumentInfo currentDocumentInfo, std::wstring javaFilePath, std::wstring classFilePath);
	public:
		RunAction(
			std::shared_ptr<ConfigurationProvider> configurationProvider,
			std::shared_ptr<ConfigurationValidator> configurationValidator,
			std::shared_ptr<ConsoleLogger> consoleLogger,
			std::shared_ptr<NppGateway> nppGateway,
			std::shared_ptr<CommandPrompt> commandPrompt)
			: configurationProvider(configurationProvider),
			configurationValidator(configurationValidator),
			consoleLogger(consoleLogger),
			nppGateway(nppGateway),
			commandPrompt(commandPrompt) {}

		void Initialize();

		void Execute();

		std::shared_ptr<ShortcutKey> getShortcutKey();
	};
}
