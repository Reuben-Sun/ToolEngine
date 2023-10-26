#pragma once

#include <string>
#include "include/common/macro.h"
#include "include/file/asset_manager.h"
#include "include/logic/input_manager.h"

namespace ToolEngine
{
	class GlobalContext
	{
	public:
		void init(std::string exe_path);
		void clear();
		
		class AssetManager* asset_manager = nullptr;
		class InputManager* input_manager = nullptr;
	private:

	};

	extern GlobalContext g_global_context;
}