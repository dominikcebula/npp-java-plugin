#include "ShowAboutDialogAction.h"

namespace NppJavaPlugin {

	void ShowAboutDialogAction::Execute() {
		aboutDialog->display(true);
	}
}
