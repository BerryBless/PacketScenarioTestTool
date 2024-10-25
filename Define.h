#pragma once

#define SAFE_DELETE(ptr) do{\
if(ptr != nullptr) \
{ \
	free(ptr); ptr = nullptr; }\
} while (0)

// TODO 크래쉬, 에레벨 나누기, 파라미터 받기
#define LOG_ERROR(msg) std::cout << msg




typedef int BOT_STATE_ID;