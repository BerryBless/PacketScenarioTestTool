#pragma once

//////////////////////////////////////////////////////////////////////////
// 봇 테스트 옵션 매니져
// TestOption을 JSON으로 양방향 파싱
//////////////////////////////////////////////////////////////////////////

#include "TestDefine.h"

class TestOptionManager
{
// 	// 싱글톤
// public:
// 	static TestOptionManager& Instance()
// 	{
// 		static TestOptionManager instance;
// 		return instance;
// 	}
// 
// private:
// 	TestOptionManager();
// 	~TestOptionManager() {}
// 
// 	//싱글톤 사용시 혹시모를 복제 차단
// 	TestOptionManager(const TestOptionManager&) = delete;
// 	TestOptionManager& operator=(const TestOptionManager&) = delete;
// 	TestOptionManager(TestOptionManager&&) = delete;
// 	TestOptionManager& operator=(TestOptionManager&&) = delete;

public:
	bool LoadSetting(std::wstring path);
	void ExtractSetting(std::wstring path);

public:
	const TestOption& GetTestOption() const { return test_option_; }

	void SetBotCount(int bot_cnt) { test_option_.bot_count = bot_cnt; }
	void SetThreadCount(int thread_count) { test_option_.thread_count = thread_count; }
	void SetAutoLogin(bool is_auto_login) { test_option_.is_auto_login = is_auto_login; }
	void SetRepeat(int is_repeat) { test_option_.is_repeat = is_repeat; }
	void SetActionList(const std::vector<ActionType>& action_list) { test_option_.action_list = action_list; }

private:
	TestOption test_option_;
};

