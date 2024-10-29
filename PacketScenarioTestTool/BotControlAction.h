#pragma once
#include "BotControlState.h"
#include "ControlEventReceiver.h"

class BotControlAction : public BotControlState
{
public:
	BotControlAction(ACTION_TYPE node_type) : BotControlState(node_type) {}
};


template<ACTION_TYPE TNodeType>
class TBotControlAction : public BotControlAction
{
public:
	static const ACTION_TYPE cNodeType = TNodeType;//ACTION_TYPE::Invalid;

	TBotControlAction() : BotControlAction(cNodeType) {}


	void	OnEnter() override { LOG_INFO("OnEnter()"); }
	void	OnExit() override { LOG_INFO("OnExit()"); }

	// 컨트롤러에서 이벤트 받아옴
	EStatus OnEvent(ControlEvent* control_event)
	{
		if (control_event == nullptr)
		{
			LOG_ERROR("control_event == nullptr");
			return ControlState::EStatus::SystemError;
		}

		// 이상태는 더이상 변경이 일어나면 안됨
		if (GetStatus() == ControlState::EStatus::SystemError)
		{
			return GetStatus();
		}

		// 캐스팅후 엑션에 뿌리기
		return OnActionEvent(static_cast<BotControlEvent*>(control_event));
	}
public:
	virtual EStatus OnActionEvent(BotControlEvent* control_event) { return GetStatus(); };
};


//-------------------------------------------------------------------------------------------------------------
// 템플릿으로 엑션 만들기
//-------------------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_A
///////////////////////////////////////////////////////////////////////////////////////////
class BotAction_A : public TBotControlAction<ACTION_TYPE::Action_A>
{

public:
	void		OnAttached() override;
	void		OnDetached() override { LOG_INFO("state_id : {} ) BotAction_A::OnDetached()\n", GetControlStateID()); }
	void		OnEnter() override { LOG_INFO("state_id : {} ) BotAction_A::OnEnter()\n", GetControlStateID()); }
	void		OnExit() override;
	EStatus		OnUpdate(DWORD tick_diff) override;
	EStatus		OnActionEvent(BotControlEvent* control_event) override;

private:
	// 이벤트
	void		OnEventAction_A_1(BotControlEvent_Action_A_1* control_event);
	void		OnEventAction_A_2(BotControlEvent_Action_A_2* control_event);

private:
	int cnt = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_B
///////////////////////////////////////////////////////////////////////////////////////////
class BotAction_B : public TBotControlAction<ACTION_TYPE::Action_B>
{

public:
	void		OnAttached() override { LOG_INFO("state_id : {} ) BotAction_B::OnAttached()\n", GetControlStateID()); }
	void		OnDetached() override { LOG_INFO("state_id : {} ) BotAction_B::OnDetached()\n", GetControlStateID()); }
	void		OnEnter() override { LOG_INFO("state_id : {} ) BotAction_B::OnEnter()\n", GetControlStateID()); }
	void		OnExit() override {
		LOG_INFO("state_id : {} ) BotAction_B::OnExit()\n", GetControlStateID());
	}
	EStatus		OnUpdate(DWORD tick_diff) override {
		Sleep(100);
		LOG_INFO("state_id : {} ) BotAction_B::OnUpdate() count = {}\n", GetControlStateID(), cnt);
		if (cnt >= 10) SetStatus(ControlState::EStatus::Completed);
		++cnt;
		return GetStatus();
	}

private:
	int cnt = 0;
};

