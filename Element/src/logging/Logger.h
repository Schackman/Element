#pragma once
#include <string>
#include "../util/macro.h"
#include "../core/platform/Platform.h"

namespace elm { namespace log
{
	/*enum class LogLevel
	{
		trace    = spdlog::level::level_enum::trace,
		critical = spdlog::level::level_enum::critical,
		error    = spdlog::level::level_enum::err,
		warning  = spdlog::level::level_enum::warn,
		debug    = spdlog::level::level_enum::debug,
		info     = spdlog::level::level_enum::info,
		off      = spdlog::level::level_enum::off
	};*/

	using LogLevel = spdlog::level::level_enum;

	enum class OutputType
	{
		none = 0,
		console = 1,
		file = 2,
		all
	};

	class Logger
	{
	public:
		static std::shared_ptr<Logger> Default();
		static void WithLogger(const std::string& message, LogLevel level, std::weak_ptr<Logger> pLogger = s_Default);

		Logger(std::string name, OutputType output = OutputType::console);

		~Logger() = default;

		static void Init();
		void LogMessage(const std::string& message, LogLevel level) const;
		void Trace(const std::string& message) const;
		void Critical(const std::string& message) const;
		void Error(const std::string& message) const;
		void Warning(const std::string& message) const;
		void Debug(const std::string& message) const;
		void Info(const std::string& message) const;

	private:
		static const std::string s_DefaultLoggerName;
		using SinkPool = std::array<std::shared_ptr<spdlog::sinks::sink>, 8>;
		static SinkPool s_OutputPool;
		static std::shared_ptr<Logger> s_Default;
		static bool s_Initialized;
		static std::vector<std::shared_ptr<spdlog::sinks::sink>> GetSinksFromOutputType(OutputType output);

		Logger() = default;

		std::shared_ptr<spdlog::logger> m_pLogger;
		std::shared_ptr<spdlog::logger> GetLogger() const;
	};
}}

#ifdef _DEBUG
#define ELM_LOG(...)		(elm::log::Logger::Default()->LogMessage(__VA_ARGS__))
#define ELM_TRACE(...)		(elm::log::Logger::Default()->Trace(__VA_ARGS__))
#define ELM_CRITICAL(...)	(elm::log::Logger::Default()->Critical(__VA_ARGS__))
#define ELM_ERROR(...)		(elm::log::Logger::Default()->Error(__VA_ARGS__))
#define ELM_WARNING(...)	(elm::log::Logger::Default()->Warning(__VA_ARGS__))
#define ELM_DEBUG(...)		(elm::log::Logger::Default()->Debug(__VA_ARGS__))
#define ELM_INFO(...)		(elm::log::Logger::Default()->Info(__VA_ARGS__))
#else //ifdef(_DEBUG)
#define ELM_LOG(...)
#define ELM_TRACE(...)
#define ELM_CRITICAL(...)
#define ELM_ERROR(...)
#define ELM_WARNING(...)
#define ELM_DEBUG(...)
#define ELM_INFO(...)
#endif //_DEBUG
