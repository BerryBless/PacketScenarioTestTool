#include "pch.h"
#include "TestManager.h"
#include "Bot.h"
TestManager::TestManager()
{

}

TestManager::~TestManager()
{

	for (int i = 0; i < bot_count_; ++i) {
		SAFE_DELETE( bot_list_[i]);
	}
	SAFE_DELETE_ARRAY (bot_list_);
}

void TestManager::Start(const std::vector<ActionType>& action_list, int bot_count, int thrad_count, bool is_repeat)
{
	action_list_ = action_list;
	bot_count_ = bot_count;
	is_repeat_ = is_repeat;
	thread_count_ = thrad_count > bot_count ? bot_count : thrad_count;// 봇보다 스레드가 많으면 봇개수만큼 스레드 생성
	is_running_ = true;

	bot_list_ = new Bot* [bot_count_];
	memset(bot_list_, 0, bot_count_ * sizeof(Bot*));

	// 스레드 생성
	int bots_per_thread = bot_count_ / thread_count_;

	for (int i = 0; i < thread_count_; ++i)
	{
		int start_id = i * bots_per_thread;
		int end_id = (i == thread_count_ - 1) ? bot_count_ : start_id + bots_per_thread;

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
		if(is_pause_) continue;

		cur_time = Clock_t::now();
		auto tick_diff = cur_time - pre_time;
		pre_time = cur_time;

		// tick_diff를 DWORD 형식의 밀리초 단위로 계산
		DWORD dw_tick_diff = static_cast<DWORD>(std::chrono::duration_cast<std::chrono::milliseconds>(tick_diff).count());


		// 구역 순회
		for (int i = start_id; i < end_id; ++i) {
			ControlState::EStatus status = bot_list_[i]->Update(dw_tick_diff);

			// 시나리오 처음부터
			if (status == ControlState::EStatus::Completed && is_repeat_)
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
	for (int i = 0; i < bot_count_; ++i)
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
		monitor_msg += std::format(L"[{}\t:\t{}]\n", ActionTypeToString(iter.first), iter.second);
	}

	Logger::Instance().Log(LogLevel::Info, monitor_msg);
//		LOG_INFO(monitor_msg);
}

void TestManager::PushScenario(int bot_index)
{
	for (auto iter : action_list_)
	{
		bot_list_[bot_index]->PushAction(iter);
	}
}
