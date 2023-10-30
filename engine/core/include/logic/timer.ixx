export module Timer;

import <chrono>;

namespace ToolEngine
{
	export class Timer
	{
	public:
        static void Start();

		static void Tick();

		static float DeltaTime();

		static float CurrentTime();
	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> last_time;
		static float delta_time;
	};
}