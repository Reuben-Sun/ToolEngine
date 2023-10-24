#pragma once

#include <string>
#include "include/file/asset_manager.h"

namespace ToolEngine
{
	class GlobalContext
	{
	public:
		void init(std::string exe_path);
		void clear();
		
		class AssetManager* asset_manager = nullptr;
	private:

	};

	extern GlobalContext g_global_context;
}