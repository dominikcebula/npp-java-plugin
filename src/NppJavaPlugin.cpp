#include "NppJavaPlugin.h"

std::shared_ptr<NppJavaPlugin::NppJavaPlugin> nppJavaPlugin;

std::shared_ptr<NppPlugin> createPlugin(HANDLE hModule) {
	nppJavaPlugin = std::make_shared<NppJavaPlugin::NppJavaPlugin>(hModule);

	return nppJavaPlugin;
}

void destroyPlugin() {
	nppJavaPlugin.reset();
}

namespace NppJavaPlugin {

	const TCHAR* NppJavaPlugin::getName() {
		return _T("Java Plugin");
	}

	void NppJavaPlugin::Initialize(NppData nppData) {
		InitializeLibraries();
		InitializeDependencies(nppData);
		InitializeCommands();
	}

	void NppJavaPlugin::InitializeLibraries() {
		LoadLibrary(_T("Riched20.dll"));
	}

	void NppJavaPlugin::InitializeDependencies(NppData nppData)
	{
		console->Initialize(nppData);
		nppGateway->Initialize(nppData);
		compileAction->Initialize();
		runAction->Initialize();
		compileAndRunAction->Initialize();
		clearConsoleAction->Initialize();
		showHideJavaConsoleAction->Initialize();
		aboutDialog->Initialize(nppData);
	}

	void NppJavaPlugin::InitializeCommands()
	{
		setCommand(0, _T("Compile"), compileActionAdapter, &*compileAction->getShortcutKey(), false);
		setCommand(1, _T("Run"), runActionAdapter, &*runAction->getShortcutKey(), false);
		setCommand(2, _T("Compile and Run"), compileAndRunActionAdapter, &*compileAndRunAction->getShortcutKey(), false);
		setCommand(3, _T("---"), NULL, NULL, false);
		setCommand(4, _T("Clear Java Console"), clearConsoleActionExecutorAdapter, &*clearConsoleAction->getShortcutKey(), false);
		setCommand(5, _T("Show/Hide Java Console"), showHideJavaConsoleActionExecutorAdapter, &*showHideJavaConsoleAction->getShortcutKey(), false);
		setCommand(6, _T("---"), NULL, NULL, false);
		setCommand(7, _T("About..."), showAboutDialogActionExecutorAdapter, NULL, false);
	}

	const size_t NppJavaPlugin::getNumberOfActions() {
		return 8;
	}

	void compileActionAdapter() {
		nppJavaPlugin->compileActionExecutor();
	}

	void NppJavaPlugin::compileActionExecutor()
	{
		compileAction->Execute();
	}

	void runActionAdapter() {
		nppJavaPlugin->runActionExecutor();
	}

	void NppJavaPlugin::runActionExecutor()
	{
		runAction->Execute();
	}

	void compileAndRunActionAdapter() {
		nppJavaPlugin->compileAndRunActionExecutor();
	}

	void NppJavaPlugin::compileAndRunActionExecutor()
	{
		compileAndRunAction->Execute();
	}

	void clearConsoleActionExecutorAdapter() {
		nppJavaPlugin->clearConsoleActionExecutor();
	}

	void NppJavaPlugin::clearConsoleActionExecutor() {
		clearConsoleAction->Execute();
	}

	void showHideJavaConsoleActionExecutorAdapter() {
		nppJavaPlugin->showHideJavaConsoleActionExecutor();
	}

	void NppJavaPlugin::showHideJavaConsoleActionExecutor() {
		showHideJavaConsoleAction->Execute();
	}

	void showAboutDialogActionExecutorAdapter() {
		nppJavaPlugin->showAboutDialogActionExecutor();
	}

	void NppJavaPlugin::showAboutDialogActionExecutor() {
		showAboutDialogAction->Execute();
	}
}
