#pragma once

#include <memory>

#include "Components/JavaConsole.h"

namespace NppJavaPlugin {

	class ShowHideJavaConsoleAction
	{
	private:
		std::shared_ptr<JavaConsole> console;

		std::shared_ptr<ShortcutKey> shortcutKey;

		void InitializeShortcutKey();
	public:
		ShowHideJavaConsoleAction(std::shared_ptr<JavaConsole> console) : console(console) {}

		void Initialize();

		void Execute();

		std::shared_ptr<ShortcutKey> getShortcutKey();
	};
}
