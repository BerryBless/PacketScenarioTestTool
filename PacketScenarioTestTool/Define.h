#pragma once


//////////////////////////////////////////
// 프로젝트 공동으로 쓸 각종 정의
//////////////////////////////////////////


// 삭제전 null 체크
#define SAFE_DELETE(ptr) do{if(ptr != nullptr) { delete(ptr); ptr = nullptr; }} while (0)
//#define SAFE_DELETE(ptr) delete(ptr)

#define SAFE_DELETE_ARRAY(ptr) do{if(ptr != nullptr) { delete[](ptr); ptr = nullptr; }} while (0)
//#define SAFE_DELETE(ptr) delete(ptr)

// 50ms = 20 FPS
#define TARGET_FRAME_DURATION_MS 500

const unsigned int PRINT_BUF_SIZE = 8192;


#define kDefaultServerIp L"127.0.0.1"
#define kDefaultServerPort 11000

// 스레드
// 하드웨어의 로직 스레드 개수
//#define kLogicThreadCount std::thread::hardware_concurrency()
#define kLogicThreadCount 4
#define kLogicThreadSleepTime 1

using Clock_t = std::chrono::system_clock;
using TimePoint_t = std::chrono::system_clock::time_point;
using TimePointOpt_t = std::optional<TimePoint_t>;
using Duration_t = std::chrono::system_clock::duration;