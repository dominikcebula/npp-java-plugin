#pragma once

#include <memory>

#include "Components/JavaConsole.h"

namespace NppJavaPlugin {

	class ClearConsoleAction
	{
	private:
		std::shared_ptr<JavaConsole> console;

		std::shared_ptr<ShortcutKey> shortcutKey;

		void InitializeShortcutKey();
	public:
		ClearConsoleAction(std::shared_ptr<JavaConsole> console) : console(console) {}

		void Initialize();

		void Execute();

		std::shared_ptr<ShortcutKey> getShortcutKey();
	};
}
