#include "pch.h"
#include "Main.h"
#include "ControlEventReceiver.h"
#include "Bot.h"
#include "FileLogger.h"

void producer(int id) {
	while (true)
	{
		LOG_WARNING(L"test tid [{}]", id);
	}
}



int main()
{
// 	std::vector<Bot*> test;
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		Bot* temp = new Bot(i);
// 		temp->PushAction(ACTION_TYPE::Action_A);
// 		test.push_back(temp);
// 	}
// 	while (true)
// 	{
// 		for (auto iter : test)
// 		{
// 			iter->Update(1000);
// 		}
// 		Sleep(1000);
// 	}

	const int numProducers = 3;
	std::vector<std::thread> producers;


	FileLogger::Instance().Init(L"test",L"log");
 
	FileLogger::Instance().ThreadStart();

	for (int i = 0; i < numProducers; ++i) {
		producers.emplace_back(producer, i + 1);
	}

	while (true)
	{
		Sleep(1000);
	}

	return 0;
}
