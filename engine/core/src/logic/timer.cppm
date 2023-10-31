import <chrono>;
import Timer;

namespace ToolEngine
{
	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::last_time;
	float Timer::delta_time = 0.0f;

    void Timer::Start()
    {
        last_time = std::chrono::high_resolution_clock::now();
    }

    void Timer::Tick()
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        delta_time = std::chrono::duration<float, std::ratio<1, 1>>(current_time - last_time).count();
        last_time = current_time;
    }

    float Timer::DeltaTime()
    {
        return delta_time;
    }

    float Timer::CurrentTime()
    {
        return std::chrono::duration<float, std::ratio<1, 1>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }
}