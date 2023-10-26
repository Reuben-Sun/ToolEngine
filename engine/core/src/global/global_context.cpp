#include "include/global/global_context.h"

namespace ToolEngine
{
	GlobalContext g_global_context;

	void GlobalContext::init(std::string exe_path)
	{
		m_asset_manager = std::make_unique<AssetManager>(exe_path);
		m_input_manager = std::make_unique<InputManager>();
		m_log_manager = std::make_unique<LogManager>();
	}
	void GlobalContext::clear()
	{
		m_asset_manager.reset();
		m_input_manager.reset();
		m_log_manager.reset();
	}
}