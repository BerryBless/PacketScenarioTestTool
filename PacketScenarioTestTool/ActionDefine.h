#pragma once
#include "EnumParser.h"
#include <unordered_map>

// 테스트 액션별 따로 나누기
// BotControlActionFactory에서 이 타입으로 액션 객체 생성
enum class ActionType
{
	Controller, // 컨트롤러 
	LogIn = 1000, // 로그인
	Action_A, // 액션 A
	Action_B, // 엑션 B 

	EndAction,
	Invalid = -1
};

// 모니터링할때 문자열을 파싱
template<>
std::unordered_map<std::wstring, ActionType> EnumParser<ActionType, std::wstring>::enum_map_ =
{
	{L"Controller", ActionType::Controller},
	{L"LogIn", ActionType::LogIn},
	{L"Action_A", ActionType::Action_A},
	{L"Action_B", ActionType::Action_B},
	{L"EndAction", ActionType::EndAction},
	{L"Invalid", ActionType::Invalid}

};



// 패킷별, 이벤트별 따로파기
enum class ActionEventType
{
	// Action A 에서 일어날 이벤트
	A_Event_1 = 1000,
	Action_A_2,
	Action_A_3,
	// Action B 에서 일어날 이벤트
	Action_B_1 = 2000,
	Invalid = -1
};
