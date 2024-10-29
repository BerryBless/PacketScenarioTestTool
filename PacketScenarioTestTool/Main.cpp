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

	std::vector<ActionType> test_list = { ActionType::LogIn, ActionType::Action_A, ActionType::Action_B };

	manager.Start(test_list, 10000000, std::thread::hardware_concurrency(), true);
	while (true)
	{
		manager.MonitorCurAction();
		Sleep(1000);
	}

	return 0;
}
