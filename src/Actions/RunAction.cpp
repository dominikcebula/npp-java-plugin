#include "RunAction.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	void RunAction::Initialize()
	{
		InitializeShortcutKey();
	}

	void RunAction::InitializeShortcutKey() {
		shortcutKey = std::make_shared<ShortcutKey>();

		shortcutKey->_isCtrl = false;
		shortcutKey->_isAlt = false;
		shortcutKey->_isShift = true;
		shortcutKey->_key = VK_F9;
	}

	std::shared_ptr<ShortcutKey> RunAction::getShortcutKey() {
		return shortcutKey;
	}

	void RunAction::Execute()
	{
		std::shared_ptr<Configuration> configuration = configurationProvider->getConfiguration();
		DocumentInfo currentDocumentInfo = nppGateway->GetCurrentDocumentInfo();
		std::wstring javaFilePath = currentDocumentInfo.currentPath;
		std::wstring classFilePath = replaceExtension(javaFilePath, _T(".class"));

		consoleLogger->Info(std::wstring().append(_T("Running File \"")).append(currentDocumentInfo.fileName).append(_T("\" in command prompt...")).c_str());

		if (!Validate(configuration, currentDocumentInfo, javaFilePath, classFilePath))
			return;

		std::wstring className = removeExtension(currentDocumentInfo.fileName);
		CommandInfo commandInfo(BuildRunCommand(currentDocumentInfo, className, configuration), currentDocumentInfo.currentDirectory);

		bool executionResult = commandPrompt->Execute(commandInfo);

		if (executionResult)
			consoleLogger->Success(std::wstring().append(_T("Executed java file \"")).append(classFilePath).append(_T("\" in command prompt.")).c_str());
		else
			consoleLogger->Error(std::wstring().append(_T("Error occured when trying to execute java file \"")).append(currentDocumentInfo.fileName)
				.append(_T("\", error details: ")).append(GetLastErrorAsString()).c_str());
	}

	bool RunAction::Validate(std::shared_ptr<Configuration> configuration, DocumentInfo currentDocumentInfo, std::wstring javaFilePath, std::wstring classFilePath) {
		if (!configurationValidator->Validate(configuration)) {
			consoleLogger->Error(_T("Detected invalid configuration, run action will not be perfomred."));
			return false;
		}

		if (currentDocumentInfo.currentDirectory.empty()) {
			consoleLogger->Error(std::wstring().append(_T("Current File \"")).append(currentDocumentInfo.fileName).append(_T("\" is not saved to disk, run will not be performed.")).c_str());
			return false;
		}


		if (!hasFileExtension(javaFilePath, _T(".java"))) {
			consoleLogger->Error(std::wstring().append(_T("Current active file \"")).append(currentDocumentInfo.fileName)
				.append(_T("\" does not have \".java\" extension, only \".java\" files are supported, execution will not be performed.")).c_str());
			return false;
		}

		if (!fileExists(classFilePath)) {
			consoleLogger->Error(std::wstring().append(_T("Compiled class file \"")).append(classFilePath)
				.append(_T("\" does not exists, Compile Action needs to be executed prior Run Action.")).c_str());
			return false;
		}

		return true;
	}

	std::wstring RunAction::BuildRunCommand(DocumentInfo currentDocumentInfo, std::wstring className, std::shared_ptr<Configuration> configuration) {
		std::wstring runCommand;

		runCommand.append(_T("cmd /C ("));
		runCommand.append(_T("\""));
		runCommand.append(configuration->getJavaPath());
		runCommand.append(_T("\""));
		runCommand.append(_T(" "));
		runCommand.append(_T("\""));
		runCommand.append(className);
		runCommand.append(_T("\""));
		runCommand.append(_T("& echo: & echo Program finished execution. & pause )"));

		return runCommand;
	}
}
