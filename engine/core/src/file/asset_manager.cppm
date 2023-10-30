import <string>;
import <vector>;
import <fstream>;
import <filesystem>;

import AssetManager;

namespace ToolEngine
{
    AssetManager::AssetManager(std::string exe_path): m_exe_path(exe_path)
	{
	}
	AssetManager::~AssetManager()
	{
	}
	std::vector<char> AssetManager::readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("failed to open file!");
		}

		size_t file_size = (size_t)file.tellg();
		std::vector<char> buffer(file_size);

		file.seekg(0);
		file.read(buffer.data(), file_size);

		file.close();

		return buffer;
	}
	std::string AssetManager::getExeFolderPath() const
	{
		return m_exe_path.parent_path().string();
	}
	std::string AssetManager::getShaderPath() const
	{
		return getExeFolderPath() + "\\shaders\\";
	}
	std::string AssetManager::getImagePath() const
	{
		return getExeFolderPath() + "\\textures\\";
	}
	std::string AssetManager::getModelsPath() const
	{
		return getExeFolderPath() + "\\models\\";
	}
}