#pragma once

#include <thread>

#include "Components/ConsoleLogger.h"
#include "Command.h"

namespace NppJavaPlugin {

	class LoggingCommandExecutor
	{
	private:
		std::shared_ptr<ConsoleLogger> consoleLogger;

	public:
		LoggingCommandExecutor(std::shared_ptr<ConsoleLogger> consoleLogger) : consoleLogger(consoleLogger) {}

		void LoggingCommandExecutor::Execute(CommandInfo commandInfo, int timeoutInMillis, std::shared_ptr<TimeoutableCommandCompletionHandler> commandCompletionHandler);
	};

	class LoggingCommand {
	private:
		std::shared_ptr<ConsoleLogger> consoleLogger;

		std::shared_ptr<PROCESS_INFORMATION> CreateChildProcess(CommandInfo commandInfo, HANDLE hChildStdOutWrite);
		void ReadFromPipeInThread(HANDLE hChildStdOutRead);
		bool WaitForProcess(std::shared_ptr<PROCESS_INFORMATION> piProcInfo, int timeoutInMillis);
		void TerminateTimeoutedProcess(std::shared_ptr<PROCESS_INFORMATION> piProcInfo);
		int ReadExitCode(std::shared_ptr<PROCESS_INFORMATION> piProcInfo);
	public:
		LoggingCommand(std::shared_ptr<ConsoleLogger> consoleLogger) : consoleLogger(consoleLogger) {}

		void ExecuteInThread(CommandInfo commandInfo, int timeoutInMillis, std::shared_ptr<TimeoutableCommandCompletionHandler> commandCompletionHandler);
	};

	class PipeReader {
	private:
		std::shared_ptr<ConsoleLogger> consoleLogger;
	public:
		PipeReader(std::shared_ptr<ConsoleLogger> consoleLogger) : consoleLogger(consoleLogger) {}

		void ReadFromPipe(HANDLE hChildStdOutRead);
	};
}
