#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <../util/fileio.h>

#define TEXT_BITS		(WORD)0x0F
#define BG_BITS			(WORD)0xF0
#define BRIGHT_BIT		(WORD)0b1000

#define BLACK			(WORD)0b000
#define WHITE			(WORD)0b001
#define YELLOW			(WORD)0b010
#define MAGENTA			(WORD)0b011
#define RED				(WORD)0b100
#define CYAN			(WORD)0b101
#define GREEN			(WORD)0b110
#define BLUE			(WORD)0b111

namespace elm { namespace log
{
	enum class LogLevel
	{
		fatal, error, warning, info
	};

	template<typename T>
	class Logger
	{
	public:
		static std::shared_ptr<Logger<T>> Get();

		Logger();

		~Logger()
		{
			Dump();
		}

		void Log(const std::string& message, LogLevel level);
		void Fatal(const std::string& message);
		void Error(const std::string& message);
		void Warning(const std::string& message);
		void Info(const std::string& message);
		void Dump();

	private:
		HANDLE m_ConsoleHandle;
		WORD m_OriginalColor;
		WORD m_Color;
		std::string m_FileName;
		std::vector<std::string> m_LogLines;

		void SetColor(const WORD& color);
		void Print(const std::string& message) const;

		static std::shared_ptr<Logger<T>> s_Instance;
	};

	template<typename T>
	std::shared_ptr<Logger<T>> Logger<T>::s_Instance = std::make_shared<Logger<T>>();

	template <typename T>
	std::shared_ptr<Logger<T>> Logger<T>::Get()
	{
		if (!s_Instance)
		{
			s_Instance = std::make_shared<Logger<T>>();
		}
		return s_Instance;
	}

	template <typename T>
	Logger<T>::Logger() :
		m_ConsoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) },
		m_OriginalColor{},
		m_Color{}
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(m_ConsoleHandle, &info);
		m_OriginalColor = info.wAttributes;
		m_Color = m_OriginalColor;
		m_LogLines.reserve(20);

		//auto sysTime = std::time(nullptr);
		//auto formattedTime = std::put_time(localtime_(&sysTime), "%F_%H-%M-%S");

		std::stringstream filename{};
		filename << "LOG_" << rand() << ".txt";
		m_FileName = filename.str();
	}

	template <typename T>
	void Logger<T>::Fatal(const std::string& message)
	{
		Log(message, LogLevel::fatal);
	}

	template <typename T>
	void Logger<T>::Error(const std::string& message)
	{
		Log(message, LogLevel::error);
	}

	template <typename T>
	void Logger<T>::Warning(const std::string& message)
	{
		Log(message, LogLevel::warning);
	}

	template <typename T>
	void Logger<T>::Info(const std::string& message)
	{
		Log(message, LogLevel::info);
	}

	template <typename T>
	void Logger<T>::Dump()
	{
		utils::AppendStringsToFile(m_FileName, m_LogLines.data(), m_LogLines.size());
		m_LogLines.clear();
	}

	template <typename T>
	void Logger<T>::SetColor(const WORD& color)
	{
		m_Color = color;
	}

	template <typename T>
	void Logger<T>::Print(const std::string& message) const
	{
		SetConsoleTextAttribute(m_ConsoleHandle, m_Color);
		std::cout << message;
		SetConsoleTextAttribute(m_ConsoleHandle, m_OriginalColor);
	}

	template <typename T>
	void Logger<T>::Log(const std::string& message, LogLevel level)
	{
		//auto sysTime = std::time(nullptr);
		//auto localTime = localtime(&sysTime);
		//auto formattedTime = std::put_time(localTime, "(%T)");
		std::string lvlString{};

		switch (level)
		{
		case LogLevel::fatal:
			SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED);
			lvlString = "[FATAL]";
			break;
		case LogLevel::error:
			SetColor(RED, true);
			SetBgColor(BLACK, false);
			lvlString = "[ERROR]";
			break;
		case LogLevel::warning:
			SetColor(YELLOW, true);
			SetBgColor(BLACK, false);
			lvlString = "[WARNING]";
			break;
		case LogLevel::info:
			SetColor(GREEN, true);
			SetBgColor(BLACK, false);
			lvlString = "[INFO]";
			break;
		default:
			SetColor(WHITE, false);
			SetBgColor(BLACK, false);
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