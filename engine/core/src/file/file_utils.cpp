#include "include/file/file_utils.h"

namespace ToolEngine
{
    std::vector<char> ToolEngine::FileUtils::readFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }
    std::string FileUtils::getWorkspacePath()
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        return currentPath.string();
    }
}
