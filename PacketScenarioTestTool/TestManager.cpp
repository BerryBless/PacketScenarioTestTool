#include "pch.h"
#include "TestManager.h"
#include "Bot.h"
TestManager::TestManager()
{

}

TestManager::~TestManager()
{

	for (int i = 0; i < test_option_.bot_count; ++i) {
		SAFE_DELETE(bot_list_[i]);
	}
	SAFE_DELETE_ARRAY(bot_list_);
}

void TestManager::Init(const TestOption& test_option)
{
	test_option_.action_list	= test_option.action_list;
	test_option_.bot_count		= test_option.bot_count;
	test_option_.is_repeat		= test_option.is_repeat;
	test_option_.thread_count	= test_option.thread_count > test_option.bot_count ? test_option.bot_count : test_option.thread_count;// 봇보다 스레드가 많으면 봇개수만큼 스레드 생성
}

void TestManager::Start()
{
	if (test_option_.action_list.empty())
	{
		LOG_ERROR(L"ActionList is Empty");
		return;
	}

	is_running_ = true;

	bot_list_ = new Bot * [test_option_.bot_count];
	memset(bot_list_, 0, test_option_.bot_count * sizeof(Bot*));

	// 스레드 생성
	int bots_per_thread = test_option_.bot_count / test_option_.thread_count;

	for (int i = 0; i < test_option_.thread_count; ++i)
	{
		int start_id = i * bots_per_thread;
		int end_id = (i == test_option_.thread_count - 1) ? test_option_.bot_count : start_id + bots_per_thread;

		// 각 스레드가 무한 루프 내에서 Update를 호출
		threads_.emplace_back(&TestManager::ThreadLoop, this, start_id, end_id);
	}

}

void TestManager::ThreadLoop(int start_id, int end_id)
{
	// 봇생성
	for (int i = start_id; i < end_id; ++i)
	{
		bot_list_[i] = new Bot(i);
	}


	TimePoint_t pre_time = Clock_t::now();
	TimePoint_t cur_time;

	while (is_running_)
	{
		

		cur_time = Clock_t::now();
		auto tick_diff = cur_time - pre_time;
		pre_time = cur_time;

		// tick_diff를 DWORD 형식의 밀리초 단위로 계산
		DWORD dw_tick_diff = static_cast<DWORD>(std::chrono::duration_cast<std::chrono::milliseconds>(tick_diff).count());


		// 구역 순회
		for (int i = start_id; i < end_id; ++i) {
			while (is_pause_) { std::this_thread::sleep_for(frame_duration_); } // 일시정지면 무한루프 돌게하기
			ControlState::EStatus status = bot_list_[i]->Update(dw_tick_diff);

			// 시나리오 처음부터
			if (status == ControlState::EStatus::Completed && test_option_.is_repeat)
			{
				PushScenario(i);
			}
		}

		// 프레임 시간 맞추기
		auto sleep_time = (tick_diff < frame_duration_) ? (frame_duration_ - tick_diff) : std::chrono::milliseconds(0);
		std::this_thread::sleep_for(sleep_time);
	}
}

void TestManager::Stop()
{
	is_running_ = false;
	for (auto& thread : threads_)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
	threads_.clear();
}


void TestManager::MonitorCurAction()
{
	std::map<ActionType, int> helper;
	for (int i = 0; i < test_option_.bot_count; ++i)
	{
		if (bot_list_[i] == nullptr) continue;

		ActionType cur_action = bot_list_[i]->GetCurrentAction();

		auto find_iter = helper.find(cur_action);
		if (find_iter == helper.end())
		{
			helper.emplace(std::make_pair(cur_action, 1));
		}
		else
		{
			find_iter->second += 1;
		}
	}

	std::wstring monitor_msg = std::format(L"\nCurrent Action count:{}\n[Action\t:\tCount]\n", helper.size());
	for (auto iter : helper)
	{
		monitor_msg += std::format(L"[{}\t:\t{}]\n", EnumParser<ActionType, std::wstring>::EnumToString(iter.first), iter.second);
	}

	LOG_INFO(L"{}", monitor_msg);
}

void TestManager::PushScenario(int bot_index)
{
	if (test_option_.action_list.empty())
	{
		LOG_ERROR(L"ActionList is Empty");
		return;
	}
	for (auto iter : test_option_.action_list)
	{
		bot_list_[bot_index]->PushAction(iter);
	}
}
