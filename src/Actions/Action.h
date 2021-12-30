#pragma once

namespace NppJavaPlugin {

	class ActionCompletionHandler {
	public:
		virtual void OnSuccess() = 0;
	};

	class DefaultActionCompletionHandler : public ActionCompletionHandler {
	public:
		void OnSuccess() {}
	};

}
