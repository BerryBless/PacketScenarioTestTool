#pragma once
#include "ActionDefine.h"

// 테스트 옵션
struct TestOption
{
	// 봇 개수
	int bot_count = 0;
	// 봇 돌릴 스레드 개수
	int thread_count = 0;
	// 자동 로그인
	bool is_auto_login = false;
	// 시나리오 반복
	bool is_repeat = false;
	// 시나리오 리스트
	std::vector<ActionType> action_list;
};

