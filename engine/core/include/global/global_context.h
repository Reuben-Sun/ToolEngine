#pragma once

#include <string>
#include "include/common/macro.h"

import LogManager;
import AssetManager;
import InputManager;
import <memory>;

namespace ToolEngine
{
	class GlobalContext
	{
	public:
		void init(std::string exe_path);
		void clear();
		
		std::shared_ptr<AssetManager> m_asset_manager {nullptr};
		std::shared_ptr<InputManager> m_input_manager {nullptr};
		std::shared_ptr<LogManager> m_log_manager	{nullptr};
	private:

	};

	extern GlobalContext g_global_context;
}