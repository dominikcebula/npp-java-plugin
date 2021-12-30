#pragma once

#include "CompileAction.h"
#include "RunAction.h"

namespace NppJavaPlugin {

	class CompileAndRunAction
	{
	private:
		std::shared_ptr<CompileAction> compileAction;
		std::shared_ptr<RunAction> runAction;

		std::shared_ptr<ShortcutKey> shortcutKey;

		void InitializeShortcutKey();
	public:
		CompileAndRunAction(std::shared_ptr<CompileAction> compileAction, std::shared_ptr<RunAction> runAction) :
			compileAction(compileAction), runAction(runAction) {}

		void Initialize();

		void Execute();

		std::shared_ptr<ShortcutKey> getShortcutKey();
	};

	class ExecuteRunAfterSuccessfullCompilation : public ActionCompletionHandler {
	private:
		std::shared_ptr<RunAction> runAction;
	public:
		ExecuteRunAfterSuccessfullCompilation(std::shared_ptr<RunAction> runAction) : runAction(runAction) {}

		void OnSuccess();
	};
}
