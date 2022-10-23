#pragma once

#include <filesystem>

namespace Hazel
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void OnImGuiRender();

	private:
		std::filesystem::path m_CurrentDirectory; //记录当前的文件层级
	};
}


