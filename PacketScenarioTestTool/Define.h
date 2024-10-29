#pragma once

#define SAFE_DELETE(ptr) do{if(ptr != nullptr) { delete(ptr); ptr = nullptr; }} while (0)
//#define SAFE_DELETE(ptr) delete(ptr)

#define SAFE_DELETE_ARRAY(ptr) do{if(ptr != nullptr) { delete[](ptr); ptr = nullptr; }} while (0)
//#define SAFE_DELETE(ptr) delete(ptr)



// 액션별 따로 나누기
enum class ACTION_TYPE
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

const unsigned int PRINT_BUF_SIZE = 8192;