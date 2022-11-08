#pragma once

#include "Hazel/Renderer/Texture.h"
#include <filesystem>


namespace Hazel
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void OnImGuiRender();

	private:
		std::filesystem::path m_CurrentDirectory; //��¼��ǰ���ļ��㼶
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}


