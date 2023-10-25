#include "include/global/global_context.h"

namespace ToolEngine
{
	GlobalContext g_global_context;

	void GlobalContext::init(std::string exe_path)
	{
		asset_manager = new AssetManager(exe_path);
		input_manager = new InputManager();
	}
	void GlobalContext::clear()
	{
		asset_manager->clear();
		input_manager->clear();

		asset_manager = nullptr;
		input_manager = nullptr;
	}
}