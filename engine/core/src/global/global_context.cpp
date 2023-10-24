#include "include/global/global_context.h"

namespace ToolEngine
{
	GlobalContext g_global_context;
	void GlobalContext::init(std::string exe_path)
	{
		asset_manager = new AssetManager(exe_path);
	}
	void GlobalContext::clear()
	{
		asset_manager = nullptr;
	}
}