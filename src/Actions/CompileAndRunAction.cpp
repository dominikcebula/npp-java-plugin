#include "CompileAndRunAction.h"

namespace NppJavaPlugin {

	void CompileAndRunAction::Initialize()
	{
		InitializeShortcutKey();
	}

	void CompileAndRunAction::InitializeShortcutKey() {
		shortcutKey = std::make_shared<ShortcutKey>();

		shortcutKey->_isCtrl = false;
		shortcutKey->_isAlt = false;
		shortcutKey->_isShift = true;
		shortcutKey->_key = VK_F10;
	}

	std::shared_ptr<ShortcutKey> CompileAndRunAction::getShortcutKey() {
		return shortcutKey;
	}

	void CompileAndRunAction::Execute() {
		compileAction->Execute(std::make_shared<ExecuteRunAfterSuccessfullCompilation>(runAction));
	}

	void ExecuteRunAfterSuccessfullCompilation::OnSuccess() {
		runAction->Execute();
	}
}
