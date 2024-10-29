#ifndef PCH_H
#define PCH_H

#pragma warning(disable: 4819)

// 여기에 미리 컴파일하려는 헤더 추가

#include <bitset>
#include <iostream>
#include <array>
#include <ranges>
#include <optional>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <list>
#include <vector>
#include <string>
#include <string_view>
#include <format>
#include <atltime.h>
#include "Logger.h"
#include "Define.h"
#include "CrashDump.h"
#include <memory>
#include <functional>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif	


#define kDefaultServerIp L"127.0.0.1"
#define kDefaultServerPort 11000

// 스레드
// 하드웨어의 로직 스레드 개수
//#define kLogicThreadCount std::thread::hardware_concurrency()
#define kLogicThreadCount 4
#define kLogicThreadSleepTime 1


#endif //PCH_H
