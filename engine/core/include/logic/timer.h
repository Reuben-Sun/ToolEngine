#pragma once

#include <chrono>

namespace ToolEngine
{
	class Timer
	{
	public:
        static void Start() 
        {
            last_time = std::chrono::high_resolution_clock::now();
        }

        static void Tick() 
        {
            auto current_time = std::chrono::high_resolution_clock::now();
            delta_time = std::chrono::duration<float>(current_time - last_time).count();
            last_time = current_time;
        }

        static float DeltaTime() 
        {
            return delta_time;
        }

        static float CurrentTime() 
		{
			return std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> last_time;
		static float delta_time;
	};
}