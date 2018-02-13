#include "FileExplorer.h"
#include "imgui.h"
#include <vector>
#include <filesystem>
#include <iostream>
FileExplorer FileExplorer::instance;
FileExplorer::FileExplorer()
{
}

void FileExplorer::display()
{
	if (!shouldDisplay)
		return;
	if (isDirty)
	{
		paths.clear();
		for (auto & p : std::experimental::filesystem::directory_iterator(path))
			paths.push_back(p.path().generic_string());
		isDirty = false;
	}
	ImGui::OpenPopup("File Explorer");
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(470, 390));
	if (ImGui::BeginPopupModal("File Explorer", NULL, window_flags))
	{
		if (ImGui::Button("BACK"))
		{
			int locationOfLastSlash = path.find_last_of('//');
			int locationOfFirstSlash = path.find_first_of('//');

			if (locationOfFirstSlash <= locationOfLastSlash && path.length() > 3)
			{
				path = path.substr(0, locationOfLastSlash);
				if (path.length() < 3)
					path += '//';
				isDirty = true;
			}
		}
		if (!std::experimental::filesystem::is_empty(path))
		{
			ImGui::BeginChild("directory_files", ImVec2(ImGui::GetWindowContentRegionWidth(), 300), true, ImGuiWindowFlags_HorizontalScrollbar);
			for (std::string strPath : paths)
			{
				ImGui::TextWrapped(strPath.c_str());
				if (ImGui::IsItemClicked(0))
				{
					path = strPath;
					isDirty = true;
				}
			}
			ImGui::EndChild();
		}
		else
		{
			std::cout << "\nIs empty " << path;
		}
		if (ImGui::Button("SELECT"))
		{
			*outputPath = path;
			shouldDisplay = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("CLOSE"))
		{
			shouldDisplay = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void FileExplorer::displayDialog(std::string* pathOutput)
{
	shouldDisplay = true;
	outputPath = pathOutput;
}

FileExplorer::~FileExplorer()
{
}
