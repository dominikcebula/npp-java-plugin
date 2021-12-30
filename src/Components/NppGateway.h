#pragma once

#include <string>

#include "PluginInfrastructure/PluginInterface.h"

namespace NppJavaPlugin {

	struct DocumentInfo {
		std::wstring currentPath;
		std::wstring fileName;
		std::wstring currentDirectory;
	};

	class NppGateway
	{
	private:
		NppData nppData;

		std::wstring GetCurrentDocumentInfoAttribute(int attributeType);
	public:
		void Initialize(NppData pNppData);

		DocumentInfo GetCurrentDocumentInfo();
		void SaveCurrentFile();
		void SetFocusOnScintilla();
	};
}
