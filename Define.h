#pragma once

#define SAFE_DELETE(ptr) do{\
if(ptr != nullptr) \
{ \
	delete(ptr); ptr = nullptr; }\
} while (0)

// TODO 크래쉬, 에레벨 나누기, 파라미터 받기
#define LOG_ERROR(msg) std::cout << msg
#define LOG_INFO(msg) std::cout << msg




typedef int BOT_STATE_ID;

enum class ACTION_NODE_TYPE
{
	Controller,
	Action_A,
	Action_B,
	Count,
	Invalid = -1
};