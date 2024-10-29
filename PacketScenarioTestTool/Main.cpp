#include "pch.h"
#include "Main.h"
#include "Logger.h"
#include "FileLogger.h"
#include "TestManager.h"
int main()
{
	FileLogger::Instance().Init(L"test", L"log");
	FileLogger::Instance().ThreadStart();

	Logger::Instance().SetLogLevel(LogLevel::Info);

	TestManager manager;

	std::vector<ACTION_TYPE> test_list = { ACTION_TYPE::LogIn, ACTION_TYPE::Action_A, ACTION_TYPE::Action_B };

	manager.Start(test_list, 5000,4,true);
	while (true)
	{
		Sleep(1000);
	}

	return 0;
}
