#include <chrono>
export module Timer;

namespace ToolEngine
{
	export class Timer
	{
	public:
        static void Start();

		static void Tick();

		static float DeltaTime();

		static float CurrentTime();

		static std::chrono::time_point<std::chrono::high_resolution_clock> last_time;
		static float delta_time;
	};
    float Timer::delta_time = 0.0f;
}