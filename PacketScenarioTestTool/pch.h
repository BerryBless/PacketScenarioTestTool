#ifndef PCH_H
#define PCH_H

#pragma warning(disable: 4819)
#define WIN32_LEAN_AND_MEAN

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
#include <map>


#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif	



#endif //PCH_H
