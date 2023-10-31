#include <spdlog/spdlog.h>
#include <cstdint>
#include <stdexcept>
#include <format>

export module LogManager;

namespace ToolEngine
{
	export class LogManager final
	{
	public:
		enum class LogLevel : uint8_t
		{
			Debug,
			Info,
			Warn,
			Error,
			Fatal
		};

		LogManager();
		~LogManager();

		template<typename... Args>
		void log(LogLevel level, Args&&... args)
		{
			switch (level)
			{
			case LogLevel::Debug:
				m_logger->debug(std::forward<Args>(args)...);
				break;
			case LogLevel::Info:
				m_logger->info(std::forward<Args>(args)...);
				break;
			case LogLevel::Warn:
				m_logger->warn(std::forward<Args>(args)...);
				break;
			case LogLevel::Error:
				m_logger->error(std::forward<Args>(args)...);
				break;
			case LogLevel::Fatal:
				m_logger->critical(std::forward<Args>(args)...);
				break;
			default:
				break;
			}
		}

		template<typename... Args>
		void fatalCallback(Args&&... args)
		{
			const std::string format_str = std::format(std::forward<Args>(args)...);
			throw std::runtime_error(format_str);
		}

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};
}