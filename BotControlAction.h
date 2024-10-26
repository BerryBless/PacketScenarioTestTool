#pragma once
#include "pch.h"
#include "BotControlState.h"
#include "ControlEventReceiver.h"

class BotControlAction : public BotControlState
{
public:
	BotControlAction(ACTION_NODE_TYPE node_type) : BotControlState(node_type) {}
};


template<ACTION_NODE_TYPE TNodeType>
class TBotControlAction : public BotControlAction
{
public:
	static const ACTION_NODE_TYPE cNodeType = TNodeType;//ACTION_NODE_TYPE::Invalid;

	TBotControlAction() : BotControlAction(cNodeType) {}


	void	OnEnter() override { LOG_INFO("OnEnter()"); }
	void	OnExit() override { LOG_INFO("OnExit()";) }

	EStatus OnEvent(ControlEvent* control_event)
	{
		if (control_event == nullptr)
		{
			LOG_ERROR("control_event == nullptr");
			return ControlState::EStatus::SystemError;
		}

		if (GetStatus() == ControlState::EStatus::Blocked || GetStatus() == ControlState::EStatus::SystemError)
		{
			return GetStatus();
		}

		return OnActionEvent(static_cast<BotControlEvent*>(control_event));
	}
public:
	virtual EStatus OnActionEvent(BotControlEvent* control_event) { return GetStatus(); };
};


class BotAction_A : public TBotControlAction<ACTION_NODE_TYPE::Action_A>
{

public:
	void		OnAttached() override {
		printf_s("state_id : %d ) BotAction_A::OnAttached(), Depth %d\n", GetControlStateID(), GetDepth());
	}
	void		OnDetached() override { printf_s("state_id : %d ) BotAction_A::OnDetached()\n", GetControlStateID()); }
	void		OnEnter() override { printf_s("state_id : %d ) BotAction_A::OnEnter()\n", GetControlStateID()); }
	void		OnExit() override;
	EStatus		OnUpdate(DWORD tick_diff) override;
	EStatus		OnActionEvent(BotControlEvent* control_event) override;

private:
	void		OnEventAction_A_1(BotControlEvent_Action_A_1* control_event);
	void		OnEventAction_A_2(BotControlEvent_Action_A_2* control_event);

private:
	int cnt = 0;
};


class BotAction_B : public TBotControlAction<ACTION_NODE_TYPE::Action_B>
{

public:
	void		OnAttached() override { printf_s("state_id : %d ) BotAction_B::OnAttached()\n", GetControlStateID()); }
	void		OnDetached() override { printf_s("state_id : %d ) BotAction_B::OnDetached()\n", GetControlStateID()); }
	void		OnEnter() override { printf_s("state_id : %d ) BotAction_B::OnEnter()\n", GetControlStateID()); }
	void		OnExit() override {
		printf_s("state_id : %d ) BotAction_B::OnExit()\n", GetControlStateID());
	}
	EStatus		OnUpdate(DWORD tick_diff) override {
		Sleep(100);
		printf_s("state_id : %d ) BotAction_B::OnUpdate() count = %d\n", GetControlStateID(), cnt);
		if (cnt >= 10) SetStatus(ControlState::EStatus::Completed);
		++cnt;
		return GetStatus();
	}

private:
	int cnt = 0;
};

