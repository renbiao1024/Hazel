#include "hzpch.h"
#include "ContentBrowserPanel.h"
#include <imgui/imgui.h>

namespace Hazel
{
	static const std::filesystem::path s_AssetPath = "assets";

	Hazel::ContentBrowserPanel::ContentBrowserPanel()
		:m_CurrentDirectory(s_AssetPath)
	{
	}

	void Hazel::ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		//������һ������
		if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, s_AssetPath);
			std::string filenameString = relativePath.filename().string();
			if (directoryEntry.is_directory()) //��Ŀ¼
			{
				if (ImGui::Button(filenameString.c_str()))
				{
					m_CurrentDirectory /= path.filename();
				}
			}
			else//����
			{
				if (ImGui::Button(filenameString.c_str()))
				{
				}
			}
		}
		ImGui::End();
	}

}
