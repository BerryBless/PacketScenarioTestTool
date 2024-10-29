#pragma once

enum class LogLevel
{
	Debug = 0,
	Info,
	Warning,
	Error,

	Invalid= -1
};


inline const wchar_t* LogLevelToString(LogLevel log_level)
{
	switch (log_level)
	{
	case LogLevel::Debug:
		return L"Debug";
	case LogLevel::Info:
		return L"Info";
	case LogLevel::Warning:
		return L"Warning";
	case LogLevel::Error:
		return L"Error";
	default:
		return L"";
	}
}


class Logger
{
// 싱글톤
public:
	static Logger& Instance()
	{
		static Logger instance;
		return instance;
	}

private:
	Logger();
	~Logger() {}

	//싱글톤 사용시 혹시모를 복제 차단
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

public:
	void SetLogLevel(LogLevel level) { log_level_ = static_cast<int>(level); }
	void SetPrintLogLevel(LogLevel level) { print_file_level_ = static_cast<int>(level); }

public:
	void Log(const LogLevel log_level, const std::string& log_text);
	void Log(const LogLevel log_level, const std::wstring& log_text);

private:
	void PrintLogConsol(const LogLevel log_level, const std::wstring& log_text);
	void PrintLogFile(const LogLevel log_level, const std::wstring& log_text);

private:
	int log_level_ = static_cast<int> (LogLevel::Debug);
	int print_file_level_ = static_cast<int> (LogLevel::Warning);
};


#define LOG(FLAG, LOGMSG, ...) do{ \
try {\
Logger::Instance().Log(FLAG, std::format(LOGMSG, __VA_ARGS__));\
}\
catch(...) {\
Logger::Instance().Log(FLAG, std::format("invalid format. {}({})", __FUNCTION__, __LINE__));\
}\
}while(0)


#define LOG_DEBUG(LOGMSG, ...) LOG(LogLevel::Debug, LOGMSG, __VA_ARGS__)
#define LOG_WARNING(LOGMSG, ...) LOG(LogLevel::Warning, LOGMSG, __VA_ARGS__)
#define LOG_INFO(LOGMSG, ...) LOG(LogLevel::Info, LOGMSG, __VA_ARGS__)
#define LOG_ERROR(LOGMSG, ...) LOG(LogLevel::Error, LOGMSG, __VA_ARGS__); CRASH()


