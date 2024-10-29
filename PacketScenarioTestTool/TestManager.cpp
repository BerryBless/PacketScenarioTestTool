#include "pch.h"
#include "TestManager.h"
#include "Bot.h"
TestManager::TestManager()
{

}

TestManager::~TestManager()
{
}

void TestManager::Start(const std::vector<ACTION_TYPE>& action_list, int bot_count, int thrad_count, bool is_repeat)
{
	action_list_ = action_list;
	bot_count_ = bot_count;
	is_repeat_ = is_repeat;
	thread_count_ = thrad_count < bot_count ? bot_count : thrad_count;
	is_running_ = true;


	// 봇생성
	bot_list_.reserve(bot_count);
	for (int i = 0; i < bot_count_; ++i)
	{
		bot_list_.emplace_back(i);  // Bot 생성자에 id 전달
	}

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
			ControlState::EStatus status = bot_list_[i].Update(dw_tick_diff);

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


void TestManager::PushScenario(int bot_index)
{
	for (auto iter : action_list_)
	{
		bot_list_[bot_index].PushAction(iter);
	}
}
