#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace ToolEngine
{
	class AssetManager
	{
	public:
		AssetManager(std::string exe_path);
		~AssetManager();
		std::vector<char> readFile(const std::string& filename);
		std::string getExeFolderPath() const;
		std::string getShaderPath() const;
		std::string getImagePath() const;
		std::string getModelsPath() const;
	private:
		std::filesystem::path m_exe_path;
	};
}