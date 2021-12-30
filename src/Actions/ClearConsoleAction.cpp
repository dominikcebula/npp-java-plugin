#include "ClearConsoleAction.h"

namespace NppJavaPlugin {

	void ClearConsoleAction::Initialize() {
		InitializeShortcutKey();
	}

	void ClearConsoleAction::InitializeShortcutKey() {
		shortcutKey = std::make_shared<ShortcutKey>();

		shortcutKey->_isCtrl = false;
		shortcutKey->_isAlt = false;
		shortcutKey->_isShift = true;
		shortcutKey->_key = VK_F11;
	}

	std::shared_ptr<ShortcutKey> ClearConsoleAction::getShortcutKey() {
		return shortcutKey;
	}

	void ClearConsoleAction::Execute() {
		console->Clear();
	}
}
