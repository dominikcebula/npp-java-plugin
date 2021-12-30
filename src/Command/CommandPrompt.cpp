#include "CommandPrompt.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	bool CommandPrompt::Execute(CommandInfo commandInfo) {
		TCHAR* command = wstringAsTChar(commandInfo.command);
		TCHAR* currentDirectory = wstringAsTChar(commandInfo.currentDirectory);

		PROCESS_INFORMATION piProcInfo;
		ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

		STARTUPINFO siStartInfo;
		ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
		siStartInfo.cb = sizeof(STARTUPINFO);

		BOOL createProcessResult = CreateProcess(NULL,
			command,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			currentDirectory,
			&siStartInfo,
			&piProcInfo
		);

		delete[] currentDirectory;
		delete[] command;

		return createProcessResult;
	}
}
