#pragma once
#include "ActionDefine.h"
#include "TestDefine.h"

//////////////////////////////////////////////////////////////////////////
// 봇 테스트 관리 매니져
// 멀티 스레드에서 봇에게 일을 맡김
//////////////////////////////////////////////////////////////////////////

class Bot;

class TestManager
{
public:
	TestManager();
	~TestManager();

	void Init(const TestOption& test_option);

	void Start();
	void ThreadLoop(int start_id, int end_id);
	void Stop();

	// 업데이트 일시정지
	void Pause() { is_pause_ = true; }
	void Resume() { is_pause_ = false; }

	// 모니터링 정보 수집
	void MonitorCurAction();

private:
	// 봇에게 엑션 리스트를 넣음
	void PushScenario(int bot_index);


private:
	const std::chrono::milliseconds frame_duration_{ TARGET_FRAME_DURATION_MS };
	// 봇리스트, 멀티스래드가 각 구역을 나눠서 순회
	Bot** bot_list_ = nullptr;

	std::vector<std::thread> threads_;
	bool is_running_ = false;
	bool is_pause_ = false;

	TestOption test_option_;
};

