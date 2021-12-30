#include "ShowHideJavaConsoleAction.h"

namespace NppJavaPlugin {

	void ShowHideJavaConsoleAction::Initialize() {
		InitializeShortcutKey();
	}

	void ShowHideJavaConsoleAction::InitializeShortcutKey() {
		shortcutKey = std::make_shared<ShortcutKey>();

		shortcutKey->_isCtrl = false;
		shortcutKey->_isAlt = false;
		shortcutKey->_isShift = true;
		shortcutKey->_key = VK_F12;
	}

	void ShowHideJavaConsoleAction::Execute() {
		console->display(!console->isVisible());
	}

	std::shared_ptr<ShortcutKey> ShowHideJavaConsoleAction::getShortcutKey() {
		return shortcutKey;
	}
}
