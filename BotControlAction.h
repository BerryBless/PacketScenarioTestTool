#pragma once
#include "pch.h"
#include "BotControlState.h"

class BotControllAction : public BotControlState
{
public:
	BotControllAction(ACTION_NODE_TYPE node_type) : BotControlState(node_type) {}
};


template<ACTION_NODE_TYPE TNodeType>
class TBotControllAction : public BotControllAction
{
public:
	static const ACTION_NODE_TYPE cNodeType = TNodeType;//ACTION_NODE_TYPE::Invalid;

	TBotControllAction() : BotControllAction(cNodeType) {}


	void	OnEnter() override { LOG_INFO("OnEnter()"); }
	void	OnExit() override { LOG_INFO("OnExit()";) }
};


class BotAction_A : public TBotControllAction<ACTION_NODE_TYPE::Action_A>
{

public:
	void		OnAttached() override {
		printf_s("state_id : %d ) BotAction_A::OnAttached(), Depth %d\n", GetControlStateID(), GetDepth());
	}
	void		OnDetached() override { printf_s("state_id : %d ) BotAction_A::OnDetached()\n", GetControlStateID()); }
	void		OnEnter() override { printf_s("state_id : %d ) BotAction_A::OnEnter()\n", GetControlStateID()); }
	void		OnExit() override;
	EStatus		OnUpdate(DWORD tick_diff) override { 
		Sleep(100);
		printf_s("state_id : %d ) BotAction_A::OnUpdate() count = %d\n", GetControlStateID(), cnt); 
		if (cnt >= 10) SetStatus(ControlState::EStatus::Completed);
		++cnt;
		return GetStatus();
	}
private:
	int cnt = 0;
};


class BotAction_B : public TBotControllAction<ACTION_NODE_TYPE::Action_B>
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

