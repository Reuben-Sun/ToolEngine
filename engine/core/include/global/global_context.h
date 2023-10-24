#pragma once

#include <string>

namespace ToolEngine
{
	class GlobalContext
	{
	public:
		void init(std::string exe_path);
		void clear();
		// class TextureManager* textureManager = nullptr; 
		// class FileManager* fileManager = nullptr;
		// class TimerManager* timerManager = nullptr;
	private:

	};

	extern GlobalContext g_global_context;
}