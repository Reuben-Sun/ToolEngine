export module AssetManager;

import <string>;
import <vector>;
import <filesystem>;

namespace ToolEngine
{
	/// <summary>
	/// A utils to load files
	/// TODO: fileID, load state, cache
	/// </summary>
	export class AssetManager
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