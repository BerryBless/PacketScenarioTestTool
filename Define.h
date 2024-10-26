#pragma once

#define SAFE_DELETE(ptr) do{\
if(ptr != nullptr) \
{ \
	delete(ptr); ptr = nullptr; }\
} while (0)

// TODO 크래쉬, 에레벨 나누기, 파라미터 받기
#define LOG_ERROR(msg) std::cout << msg
#define LOG_INFO(msg) std::cout << msg



// 액션별 따로 나누기
enum class ACTION_NODE_TYPE
{
	Controller,
	Action_A = 1000,
	Action_B,
	Invalid = -1
};

// 패킷별, 이벤트별 따로파기
enum class ACTION_EVENT_TYPE
{
	Action_A_1 = 1000,
	Action_A_2,
	Action_A_3,
	Action_B_1 = 2000,
	Invalid = -1
};