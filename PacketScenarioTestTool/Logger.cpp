#include "pch.h"
#include "Logger.h"
#include "FileLogger.h"

Logger::Logger()
{
}

void Logger::Log(const LogLevel log_level, const std::string& log_text)
{
	if (log_level_ > static_cast<int>(log_level))
	{
		// 로그레벨 낮음
		return;
	}

	Log(log_level, Utf8ToWstring(log_text.data()));

}

void Logger::Log(const LogLevel log_level, const std::wstring& log_text)
{

	if (log_level_ > static_cast<int>(log_level))
	{
		// 로그레벨 낮음
		return;
	}

	PrintLogConsol(log_level, log_text);
	if (print_file_level_ >= static_cast<int>(log_level))
		PrintLogFile(log_level, log_text);
}

void Logger::PrintLogConsol(const LogLevel log_level, const std::wstring& log_text)
{

	TCHAR szLogBuffer[PRINT_BUF_SIZE + 1] = { 0x00, };
	//int buff_size = sizeof( szLogBuffer );
 // 프로젝트환경 - 유니코드로 변경..
	int buff_size = _countof(szLogBuffer);
	int write_size = 0;

	SYSTEMTIME system_time;
	::GetLocalTime(&system_time);

	write_size += _stprintf_s(szLogBuffer + write_size, buff_size - write_size, L"[%d-%02d-%02d %02d:%02d:%02d:%03d] ",
		system_time.wYear,
		system_time.wMonth,
		system_time.wDay,
		system_time.wHour,
		system_time.wMinute,
		system_time.wSecond,
		system_time.wMilliseconds
	);

	write_size += _stprintf_s(szLogBuffer + write_size, buff_size - write_size, L"[%s] ", LogLevelToString(log_level));

	write_size += _stprintf_s(szLogBuffer + write_size, buff_size - write_size, L"%ls\n", log_text.c_str());

	//WriteConsole
	WriteConsoleW(::GetStdHandle(STD_OUTPUT_HANDLE), szLogBuffer, static_cast<DWORD>(wcslen(szLogBuffer)), nullptr, nullptr);
	//fwprintf( stderr, L"%s\n", szLogBuffer );
	fflush(stderr);


}

void Logger::PrintLogFile(const LogLevel log_level, const std::wstring& log_text)
{
	// 현재시간 얻기
	time_t timer = time(NULL);
	tm t;
	errno_t err;

	err = localtime_s(&t, &timer);
	if (err) {
		return;
	}

	// YYYY.MM.DD hh:mm:ss
	std::wstring log_msg = std::format(L"[{}.{}.{} {}:{}:{}] [{}]\t{}\n",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec,
		LogLevelToString(log_level),
		log_text);

	FileLogger::Instance().Write(log_msg);
}
