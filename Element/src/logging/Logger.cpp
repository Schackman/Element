#include "pch.h"
#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace elm { namespace log
{
#pragma region STATIC
	const std::string Logger::s_DefaultLoggerName{ "ELEMENT" };
	Logger::SinkPool Logger::s_OutputPool{};
	std::shared_ptr<Logger> Logger::s_Default = std::shared_ptr<Logger>{nullptr};
	bool Logger::s_Initialized{false};

	std::shared_ptr<Logger> Logger::Default()
	{
		if (!s_Initialized)
		{
			throw std::exception("Logger is not initialized!");
		}
		return s_Default;
	}

	void Logger::WithLogger(const std::string& message, LogLevel level, std::weak_ptr<Logger> pLogger)
	{
		if (auto p = pLogger.lock())
		{
			p->LogMessage(message, level);
		}
	}

	void Logger::Init()
	{
		if (s_Initialized)
			return;
	
		try
		{
			spdlog::set_pattern("%^[%T](%L) %n: %v%$");
			// console sink
			s_OutputPool[(size_t)OutputType::console] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			// Rotating file sink with 1mb size max and 3 rotated files
			s_OutputPool[(size_t) OutputType::file] = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/log.txt", 1048576, 3);
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cerr << ex.what() << std::endl;
			throw std::exception(ex);
		}

		s_Default = std::make_shared<Logger>(s_DefaultLoggerName, OutputType::console);
		//spdlog::set_default_logger(s_Default->GetLogger());
		s_Initialized = true;
	}
#pragma endregion STATIC

#pragma region MEMBER

	Logger::Logger(std::string name, OutputType output)
	{
		auto sinks{GetSinksFromOutputType(output)};
		m_pLogger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
		m_pLogger->set_level(spdlog::level::trace);
	}

	void Logger::LogMessage(const std::string& message, LogLevel level) const
	{
		m_pLogger->log((spdlog::level::level_enum)level, message);
	}

	std::vector<std::shared_ptr<spdlog::sinks::sink>> Logger::GetSinksFromOutputType(OutputType output)
	{
		std::vector <std::shared_ptr<spdlog::sinks::sink>> sinks{};
		switch (output)
		{
		case OutputType::console:
			sinks.push_back(s_OutputPool[(size_t)OutputType::console]);
			break;
		case OutputType::file:
			sinks.push_back(s_OutputPool[(size_t)OutputType::file]);
			break;
		case OutputType::all:
			sinks.push_back(s_OutputPool[(size_t)OutputType::console]);
			sinks.push_back(s_OutputPool[(size_t)OutputType::file]);
			break;
		case OutputType::none:
			break;
		}

		return sinks;
	}

	std::shared_ptr<spdlog::logger> Logger::GetLogger() const
	{
		return m_pLogger;
	}

	void Logger::Trace(const std::string& message) const
	{
		LogMessage(message, LogLevel::trace);
	}

	void Logger::Critical(const std::string& message) const
	{
		LogMessage(message, LogLevel::critical);
	}


	void Logger::Error(const std::string& message) const
	{
		LogMessage(message, LogLevel::err);
	}


	void Logger::Warning(const std::string& message) const
	{
		LogMessage(message, LogLevel::warn);
	}

	void Logger::Debug(const std::string& message) const
	{
		LogMessage(message, LogLevel::debug);
	}


	void Logger::Info(const std::string& message) const
	{
		LogMessage(message, LogLevel::info);
	}

#pragma endregion MEMBER
}}
