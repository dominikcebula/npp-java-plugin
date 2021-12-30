#pragma once

#include <memory>

#include "Components/AboutDialog.h"

namespace NppJavaPlugin {

	class ShowAboutDialogAction
	{
	private:
		std::shared_ptr<AboutDialog> aboutDialog;
	public:
		ShowAboutDialogAction(std::shared_ptr<AboutDialog> aboutDialog) : aboutDialog(aboutDialog) {}

		void Execute();
	};
}
