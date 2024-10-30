#include "pch.h"
#include "Main.h"
#include "Logger.h"
#include "FileLogger.h"
#include "TestManager.h"
#include "TestOptionManager.h"
int main()
{
	FileLogger::Instance().Init(L"test", L"log");
	FileLogger::Instance().ThreadStart();

	Logger::Instance().SetLogLevel(LogLevel::Info);

	TestOptionManager option_manager;
	TestManager test_manager;

	option_manager.LoadSetting(L"Test.json");

 	test_manager.Init(option_manager.GetTestOption());
 
 	test_manager.Start();
 	while (true)
 	{
 		test_manager.MonitorCurAction();
 		Sleep(1000);
 	}
	
	
	FileLogger::Instance().ThreadStop();

	return 0;
}
