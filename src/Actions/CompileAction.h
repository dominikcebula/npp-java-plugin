#pragma once

#include <memory>

#include "PluginInfrastructure/NppPlugin.h"
#include "Components/ConsoleLogger.h"
#include "Command/LoggingCommand.h"
#include "Components/NppGateway.h"
#include "Configuration/ConfigurationProvider.h"
#include "Configuration/ConfigurationValidator.h"
#include "Action.h"

namespace NppJavaPlugin {

	class CompileAction
	{
	private:
		std::shared_ptr<ConfigurationProvider> configurationProvider;
		std::shared_ptr<ConfigurationValidator> configurationValidator;
		std::shared_ptr<ConsoleLogger> consoleLogger;
		std::shared_ptr<NppGateway> nppGateway;
		std::shared_ptr<LoggingCommandExecutor> commandExecutor;

		std::shared_ptr<ShortcutKey> shortcutKey;

		std::wstring BuildCompilationCommand(DocumentInfo currentDocumentInfo, std::shared_ptr<Configuration> configuration);
		void InitializeShortcutKey();

		bool Validate(std::shared_ptr<Configuration> configuration, DocumentInfo currentDocumentInfo);
	public:
		CompileAction(
			std::shared_ptr<ConfigurationProvider> configurationProvider,
			std::shared_ptr<ConfigurationValidator> configurationValidator,
			std::shared_ptr<ConsoleLogger> consoleLogger,
			std::shared_ptr<NppGateway> nppGateway,
			std::shared_ptr<LoggingCommandExecutor> commandExecutor)
			: configurationProvider(configurationProvider),
			configurationValidator(configurationValidator),
			consoleLogger(consoleLogger),
			nppGateway(nppGateway),
			commandExecutor(commandExecutor) {}

		void Initialize();

		void Execute();
		void Execute(std::shared_ptr<ActionCompletionHandler> actionCompletionHandler);

		std::shared_ptr<ShortcutKey> getShortcutKey();
	};

	class CompileCommandCompletionHandler : public TimeoutableCommandCompletionHandler {
	private:
		std::shared_ptr<ConsoleLogger> consoleLogger;
		std::shared_ptr<ActionCompletionHandler> actionCompletionHandler;
		DocumentInfo currentDocumentInfo;
	public:
		CompileCommandCompletionHandler(
			std::shared_ptr<ConsoleLogger> consoleLogger,
			std::shared_ptr<ActionCompletionHandler> actionCompletionHandler,
			DocumentInfo currentDocumentInfo) :
			consoleLogger(consoleLogger),
			actionCompletionHandler(actionCompletionHandler),
			currentDocumentInfo(currentDocumentInfo) {}

		void onSuccess();
		void onFailure(int exitCode);
		void onTimeout();
	};
}
