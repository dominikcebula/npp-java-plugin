#include "CompileAction.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	constexpr int COMPILE_ACTION_TIMEOUT_IN_MILLIS = 60 * 1000;

	void CompileAction::Initialize()
	{
		InitializeShortcutKey();
	}

	void CompileAction::InitializeShortcutKey() {
		shortcutKey = std::make_shared<ShortcutKey>();

		shortcutKey->_isCtrl = false;
		shortcutKey->_isAlt = false;
		shortcutKey->_isShift = true;
		shortcutKey->_key = VK_F8;
	}

	std::shared_ptr<ShortcutKey> CompileAction::getShortcutKey() {
		return shortcutKey;
	}

	void CompileAction::Execute()
	{
		Execute(std::make_shared<DefaultActionCompletionHandler>());
	}

	void CompileAction::Execute(std::shared_ptr<ActionCompletionHandler> actionCompletionHandler)
	{
		std::shared_ptr<Configuration> configuration = configurationProvider->getConfiguration();
		DocumentInfo currentDocumentInfo = nppGateway->GetCurrentDocumentInfo();

		consoleLogger->Info(std::wstring().append(_T("Compiling File \"")).append(currentDocumentInfo.fileName).append(_T("\"...")).c_str());

		if (!Validate(configuration, currentDocumentInfo))
			return;

		nppGateway->SaveCurrentFile();

		CommandInfo commandInfo(BuildCompilationCommand(currentDocumentInfo, configuration), currentDocumentInfo.currentDirectory);
		commandExecutor->Execute(commandInfo, COMPILE_ACTION_TIMEOUT_IN_MILLIS, std::make_shared<CompileCommandCompletionHandler>(consoleLogger, actionCompletionHandler, currentDocumentInfo));
	}

	bool CompileAction::Validate(std::shared_ptr<Configuration> configuration, DocumentInfo currentDocumentInfo) {
		if (!configurationValidator->Validate(configuration)) {
			consoleLogger->Error(_T("Detected invalid configuration, compile action will not be performed."));
			return false;
		}

		if (currentDocumentInfo.currentDirectory.empty()) {
			consoleLogger->Error(std::wstring().append(_T("Current File \"")).append(currentDocumentInfo.fileName).append(_T("\" is not saved to disk, compilation will not be performed.")).c_str());
			return false;
		}

		if (!hasFileExtension(currentDocumentInfo.currentPath, _T(".java"))) {
			consoleLogger->Error(std::wstring().append(_T("Current active file \"")).append(currentDocumentInfo.fileName)
				.append(_T("\" does not have \".java\" extension, only \".java\" files are supported, compilation will not be performed.")).c_str());
			return false;
		}

		return true;
	}

	std::wstring CompileAction::BuildCompilationCommand(DocumentInfo currentDocumentInfo, std::shared_ptr<Configuration> configuration) {
		std::wstring compilationCommand;

		compilationCommand.append(_T("\""));
		compilationCommand.append(configuration->getJavacPath());
		compilationCommand.append(_T("\""));
		compilationCommand.append(_T(" "));
		compilationCommand.append(_T("\""));
		compilationCommand.append(currentDocumentInfo.currentPath);
		compilationCommand.append(_T("\""));

		return compilationCommand;
	}

	void CompileCommandCompletionHandler::onSuccess()
	{
		consoleLogger->Success(std::wstring().append(_T("File \"")).append(currentDocumentInfo.fileName).append(_T("\" compiled successfully.")).c_str());

		actionCompletionHandler->OnSuccess();
	}

	void CompileCommandCompletionHandler::onFailure(int exitCode)
	{
		consoleLogger->Error(std::wstring().append(_T("Failed to compile file \"")).append(currentDocumentInfo.fileName)
			.append(_T("\", exit code = ")).append(std::to_wstring(exitCode)).c_str());
	}

	void CompileCommandCompletionHandler::onTimeout()
	{
		consoleLogger->Error(std::wstring().append(_T("Failed to compile file \"")).append(currentDocumentInfo.fileName)
			.append(_T("\", compilation was not finished within timeout = ")).append(std::to_wstring(COMPILE_ACTION_TIMEOUT_IN_MILLIS)).c_str());
	}
}
