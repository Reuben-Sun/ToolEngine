#include "include/logic/timer.h"

namespace ToolEngine
{
	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::last_time;
	float Timer::delta_time = 0.0f;
}