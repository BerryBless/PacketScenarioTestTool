#pragma once
//////////////////////////////////////////////////////////////////////////
// 봇 관리 매니져
// Json을 읽어 봇에게 일을 맡김
//////////////////////////////////////////////////////////////////////////


class Bot;

class TestManager
{
public:
	TestManager();
	~TestManager();
	
	void Start(const std::vector<ACTION_TYPE>& action_list, int bot_count,int thrad_count, bool is_repeat);
	void ThreadLoop(int start_id, int end_id);
	void Stop();

	// 업데이트 일시정지
	void Pause() { is_pause_ = true; }
	void Resume() { is_pause_ = false; }
private:
	void PushScenario(int bot_index);

private:
	const std::chrono::milliseconds frame_duration_{ 50 }; // 50ms = 20 FPS

	int bot_count_ = 0;
	int thread_count_ = 0;

	std::vector<Bot> bot_list_;
	std::vector<std::thread> threads_;
	std::vector<ACTION_TYPE> action_list_;

	bool is_repeat_ = false;
	bool is_running_ = false;
	bool is_pause_ = false;
};

