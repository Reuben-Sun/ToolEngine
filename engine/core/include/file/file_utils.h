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
		static std::vector<char> readFile(const std::string& filename);
		static std::string getWorkspacePath();
		static std::string getRootPath();
	};
}