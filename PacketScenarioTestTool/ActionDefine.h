#pragma once
#include "EnumParser.h"
#include <unordered_map>

// 액션별 따로 나누기
enum class ActionType
{
	Controller,
	LogIn = 1000,
	Action_A,
	Action_B,

	EndAction,
	Invalid = -1
};

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
	Action_A_1 = 1000,
	Action_A_2,
	Action_A_3,
	Action_B_1 = 2000,
	Invalid = -1
};
