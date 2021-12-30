#include <tchar.h>

#include "LoggingCommand.h"
#include "Components/Utils.h"

namespace NppJavaPlugin {

	constexpr int BUFF_SIZE = 4096;

	void LoggingCommandExecutor::Execute(CommandInfo commandInfo, int timeoutInMillis, std::shared_ptr<TimeoutableCommandCompletionHandler> commandCompletionHandler) {
		std::thread commandThread(&LoggingCommand::ExecuteInThread, std::make_shared<LoggingCommand>(consoleLogger), commandInfo, timeoutInMillis, commandCompletionHandler);
		commandThread.detach();
	}

	void LoggingCommand::ExecuteInThread(CommandInfo commandInfo, int timeoutInMillis, std::shared_ptr<TimeoutableCommandCompletionHandler> commandCompletionHandler) {
		HANDLE hChildStdOutRead = NULL;
		HANDLE hChildStdOutWrite = NULL;

		SECURITY_ATTRIBUTES saAttr;
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = TRUE;
		saAttr.lpSecurityDescriptor = NULL;

		if (!CreatePipe(&hChildStdOutRead, &hChildStdOutWrite, &saAttr, 0)) {
			consoleLogger->Error(_T("Failed to create pipe for child process."));
			return;
		}

		std::shared_ptr<PROCESS_INFORMATION> piProcInfo = CreateChildProcess(commandInfo, hChildStdOutWrite);

		CloseHandle(hChildStdOutWrite);

		if (piProcInfo != nullptr) {
			ReadFromPipeInThread(hChildStdOutRead);

			if (WaitForProcess(piProcInfo, timeoutInMillis)) {
				int exitCode = ReadExitCode(piProcInfo);

				if (exitCode == 0)
					commandCompletionHandler->onSuccess();
				else
					commandCompletionHandler->onFailure(exitCode);
			}
			else {
				TerminateTimeoutedProcess(piProcInfo);

				commandCompletionHandler->onTimeout();
			}

			CloseHandle(piProcInfo->hProcess);
			CloseHandle(piProcInfo->hThread);
		}
		else
			consoleLogger->Error(std::wstring().append(_T("Failed to start the process, error details: ")).append(GetLastErrorAsString()).c_str());

		CloseHandle(hChildStdOutRead);
	}

	std::shared_ptr<PROCESS_INFORMATION> LoggingCommand::CreateChildProcess(CommandInfo commandInfo, HANDLE hChildStdOutWrite)
	{
		TCHAR* command = wstringAsTChar(commandInfo.command);
		TCHAR* currentDirectory = wstringAsTChar(commandInfo.currentDirectory);

		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;

		ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
		siStartInfo.cb = sizeof(STARTUPINFO);
		siStartInfo.hStdError = hChildStdOutWrite;
		siStartInfo.hStdOutput = hChildStdOutWrite;
		siStartInfo.hStdInput = NULL;
		siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

		BOOL createProcessResult = CreateProcess(NULL,
			command,
			NULL,
			NULL,
			TRUE,
			CREATE_NO_WINDOW,
			NULL,
			currentDirectory,
			&siStartInfo,
			&piProcInfo
		);

		delete[] currentDirectory;
		delete[] command;

		if (createProcessResult)
			return std::make_shared<PROCESS_INFORMATION>(piProcInfo);
		else
			return nullptr;
	}

	void LoggingCommand::ReadFromPipeInThread(HANDLE hChildStdOutRead)
	{
		std::thread readPipeThread(&PipeReader::ReadFromPipe, std::make_shared<PipeReader>(consoleLogger), hChildStdOutRead);
		readPipeThread.detach();
	}

	bool LoggingCommand::WaitForProcess(std::shared_ptr<PROCESS_INFORMATION> piProcInfo, int timeoutInMillis) {
		DWORD waitResult = WaitForSingleObject(piProcInfo->hProcess, timeoutInMillis);

		if (waitResult == 0)
			return true;
		else {
			std::wstring errorMessage = std::wstring().append(_T("Process did not finished within timeout = ")).append(std::to_wstring(timeoutInMillis));
			consoleLogger->Error(errorMessage.c_str());
			return false;
		}
	}

	int LoggingCommand::ReadExitCode(std::shared_ptr<PROCESS_INFORMATION> piProcInfo) {
		DWORD exitCode = 1;
		if (!GetExitCodeProcess(piProcInfo->hProcess, &exitCode)) {
			consoleLogger->Error(_T("Failed to read process exit code."));
		}
		return exitCode;
	}

	void LoggingCommand::TerminateTimeoutedProcess(std::shared_ptr<PROCESS_INFORMATION> piProcInfo) {
		consoleLogger->Warning(_T("Terminating timeouted process..."));

		BOOL terminateResult = TerminateProcess(piProcInfo->hProcess, 1);

		if (terminateResult) {
			consoleLogger->Warning(_T("Timeouted process terminated successfully."));
		}
		else {
			consoleLogger->Error(_T("Timeouted process NOT terminated."));
		}
	}

	void PipeReader::ReadFromPipe(HANDLE hChildStdOutRead)
	{
		DWORD dwRead;
		CHAR chBuff[BUFF_SIZE];
		WCHAR wChBuff[BUFF_SIZE];

		while (true)
		{
			ZeroMemory(chBuff, BUFF_SIZE);

			BOOL bSuccess = ReadFile(hChildStdOutRead, chBuff, BUFF_SIZE, &dwRead, NULL);
			if (!bSuccess || dwRead == 0)
				break;

			mbstowcs(wChBuff, chBuff, BUFF_SIZE);

			consoleLogger->Raw(wChBuff);
		}
	}
}
