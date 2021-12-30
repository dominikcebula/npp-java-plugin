#pragma once

#include <string>

namespace NppJavaPlugin {

	struct CommandInfo {
		std::wstring command;
		std::wstring currentDirectory;

		CommandInfo(std::wstring command, std::wstring currentDirectory) : command(command), currentDirectory(currentDirectory) {}
	};

	class TimeoutableCommandCompletionHandler {
	public:
		virtual void onSuccess() = 0;
		virtual void onFailure(int exitCode) = 0;
		virtual void onTimeout() = 0;
	};
}
