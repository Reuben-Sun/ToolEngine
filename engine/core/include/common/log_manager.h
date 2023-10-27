#pragma once

#include <spdlog/spdlog.h>
#include <cstdint>
#include <stdexcept>
#include <format>

namespace ToolEngine
{
	class LogManager final
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
		void log(LogLevel level, const char* _module, Args&&... args)
		{
			char char_part = 'x';
			const char* str = &char_part;
			switch (level)
			{
			case LogLevel::Debug:
				m_logger->debug(spdlog::fmt_runtime_string<char>{ _module }, std::forward<Args>(args)...);
				break;
			case LogLevel::Info:
				m_logger->info(spdlog::fmt_runtime_string<char>{ _module }, std::forward<Args>(args)...);
				break;
			case LogLevel::Warn:
				m_logger->warn(spdlog::fmt_runtime_string<char>{ _module }, std::forward<Args>(args)...);
				break;
			case LogLevel::Error:
				m_logger->error(spdlog::fmt_runtime_string<char>{ _module }, std::forward<Args>(args)...);
				break;
			case LogLevel::Fatal:
				m_logger->critical(spdlog::fmt_runtime_string<char>{ _module }, std::forward<Args>(args)...);
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