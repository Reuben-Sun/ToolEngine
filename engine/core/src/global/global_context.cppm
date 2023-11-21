#include "include/common/macro.h"
import GlobalContext;

import AssetManager;
import InputManager;
import BindingManager;


namespace ToolEngine
{
	GlobalContext g_global_context;

	void GlobalContext::init(std::string exe_path)
	{
		m_asset_manager = std::make_shared<AssetManager>(exe_path);
		m_input_manager = std::make_shared<InputManager>();
	}
	void GlobalContext::clear()
	{
		m_asset_manager.reset();
		m_input_manager.reset();
	}
}