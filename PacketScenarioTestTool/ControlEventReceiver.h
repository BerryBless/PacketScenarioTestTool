#pragma once
#include "BotControlState.h"

// ACTION_EVENT_TYPE 마다 이벤트 생성 필요
// 데이터만 넘겨줌
// OnEvent 구현은 각 Action 에서 따로하기


class BotControlEvent : public BotControlState::ControlEvent
{
public:
	// TODO ID 다시 생각하기
	BotControlEvent(ACTION_EVENT_TYPE event_type) : 
		BotControlState::ControlEvent(static_cast<BotControlState::EventId> (event_type))
	, event_type_(event_type) {}

public:
	ACTION_EVENT_TYPE GetEventType() { return event_type_; }
private:
	ACTION_EVENT_TYPE event_type_ = ACTION_EVENT_TYPE::Invalid;
};


template<ACTION_EVENT_TYPE TEventType>
class TBotControllEvent : public BotControlEvent
{
public:
	static const ACTION_EVENT_TYPE cEventType = TEventType;

	TBotControllEvent() : BotControlEvent(cEventType) {}

};

//-------------------------------------------------------------------------------------------------------------
// 템플릿으로 이벤트 만들기
//-------------------------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////
// BotControlEvent_Action_A_1
///////////////////////////////////////////////////////////////////////////////////////////
class BotControlEvent_Action_A_1 : public TBotControllEvent<ACTION_EVENT_TYPE::Action_A_1>
{
public:
	BotControlEvent_Action_A_1(std::string event_content) :
		event_content_(event_content){}

public:
	const std::string event_content_;
};



///////////////////////////////////////////////////////////////////////////////////////////
// BotControlEvent_Action_A_2
///////////////////////////////////////////////////////////////////////////////////////////
class BotControlEvent_Action_A_2 : public TBotControllEvent<ACTION_EVENT_TYPE::Action_A_2>
{
public:
	BotControlEvent_Action_A_2(int event_content) :
		event_content_(event_content) {}

public:
	const int event_content_;
};

