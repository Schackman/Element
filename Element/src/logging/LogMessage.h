#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace elm { namespace log
{
	enum class LogLevel
	{
		fatal, error, warning, info
	};

	template<typename T>
	class Log
	{
	public:
		static std::shared_ptr<Log<T>> Get();

		Log();

		~Log()
		{
			Dump();
		}

		void LogMessage(const std::string& message, LogLevel level);
		void Fatal(const std::string& message);
		void Error(const std::string& message);
		void Warning(const std::string& message);
		void Info(const std::string& message);
		void Dump();

	private:
		std::shared_ptr<spdlog::logger> m_pLogger;
		std::string m_FileName;
		std::vector<std::string> m_LogLines;

		//void SetColor(const WORD& color);
		void Print(const std::string& message) const;

		static std::shared_ptr<Log<T>> s_Instance;
	};

	template<typename T>
	std::shared_ptr<Log<T>> Log<T>::s_Instance = std::make_shared<Log<T>>();

	template <typename T>
	std::shared_ptr<Log<T>> Log<T>::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::make_shared<Log<T>>();
		}
		return s_Instance;
	}

	template <typename T>
	Log<T>::Log()
	{
		try
		{
			// Create a file rotating logger with 5mb size max and 3 rotated files
			m_pLogger = spdlog::rotating_logger_mt("elm", "logs/rotating.txt", 1048576 * 5, 3);
			auto console = spdlog::stdout_color_mt("console");
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cerr << ex.what() << std::endl;
			throw std::exception(ex);
		}
	}

	template <typename T>
	void Log<T>::Fatal(const std::string& message)
	{
		LogMessage(message, LogLevel::fatal);
	}

	template <typename T>
	void Log<T>::Error(const std::string& message)
	{
		
		LogMessage(message, LogLevel::error);
	}

	template <typename T>
	void Log<T>::Warning(const std::string& message)
	{
		LogMessage(message, LogLevel::warning);
	}

	template <typename T>
	void Log<T>::Info(const std::string& message)
	{
		LogMessage(message, LogLevel::info);
	}

	template <typename T>
	void Log<T>::Dump()
	{
//		utils::AppendStringsToFile(m_FileName, m_LogLines.data(), m_LogLines.size());
		m_LogLines.clear();
	}

	/*template <typename T>
	void Logger<T>::SetColor(const WORD& color)
	{
		m_Color = color;
	}*/

	template <typename T>
	void Log<T>::Print(const std::string& message) const
	{
		//SetConsoleTextAttribute(m_ConsoleHandle, m_Color);
		std::cout << message;
		//SetConsoleTextAttribute(m_ConsoleHandle, m_OriginalColor);
	}

	template <typename T>
	void Log<T>::LogMessage(const std::string& message, LogLevel level)
	{
		//auto sysTime = std::time(nullptr);
		//auto localTime = localtime(&sysTime);
		//auto formattedTime = std::put_time(localTime, "(%T)");
		std::string lvlString{};

		switch (level)
		{
		case LogLevel::fatal:
			//SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED);
			lvlString = "[FATAL]";
			break;
		case LogLevel::error:
			//SetColor(RED, true);
			//SetBgColor(BLACK, false);
			lvlString = "[ERROR]";
			break;
		case LogLevel::warning:
			//SetColor(YELLOW, true);
			//SetBgColor(BLACK, false);
			lvlString = "[WARNING]";
			break;
		case LogLevel::info:
			//SetColor(GREEN, true);
			//SetBgColor(BLACK, false);
			lvlString = "[INFO]";
			break;
		default:
			//SetColor(WHITE, false);
			//SetBgColor(BLACK, false);
			lvlString = "[UNKNOWN]";
			break;
		}

		std::stringstream logLine{};
		std::string name{"["};
		name += typeid(T).name();
		name += "]";
		logLine << /*formattedTime << */std::setw(10) << std::left << lvlString << std::setw(48) << std::left << name << message << std::endl;
		if (m_LogLines.size() >= m_LogLines.capacity())
		{
			Dump();
		}
		m_LogLines.push_back(logLine.str());

		Print(logLine.str());
	}
}}