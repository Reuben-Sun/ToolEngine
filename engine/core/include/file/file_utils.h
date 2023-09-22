#pragma once
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

namespace ToolEngine
{
	class FileUtils
	{
	public:
		static FileUtils& getInstance()
		{
			static FileUtils instance;
			return instance;
		}
		std::vector<char> readFile(const std::string& filename);
		void setExePath(std::string path) { exe_path = path; };
		std::string getExeFolderPath() { return exe_path.parent_path().string(); }
		std::string getShaderPath() { return getExeFolderPath() + "\\shaders\\"; }
		std::string getImagePath() { return getExeFolderPath() + "\\textures\\"; }
	private:
		FileUtils() {}
		FileUtils(FileUtils const&) = delete;
		void operator=(FileUtils const&) = delete;

		std::filesystem::path exe_path;
	};
}