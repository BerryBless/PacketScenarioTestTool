#pragma once
#include "pch.h"
#include "BotControlState.h"

class BotControllAction : public BotControlState
{
public:
	BotControllAction(ControlStateID control_state_id) : BotControlState(control_state_id) {}
};


class BotAction_A : public BotControllAction
{
public:
	BotAction_A(ControlStateID control_state_id) : BotControllAction(control_state_id) {}

public:
	void		OnAttached() override { printf_s("state_id : %d ) BotAction_A::OnAttached()\n", GetControlStateID()); }
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


class BotAction_B : public BotControllAction
{
public:
	BotAction_B(ControlStateID control_state_id) : BotControllAction(control_state_id) {}

public:
	void		OnAttached() override { printf_s("state_id : %d ) BotAction_B::OnAttached()\n", GetControlStateID()); }
	void		OnDetached() override { printf_s("state_id : %d ) BotAction_B::OnDetached()\n", GetControlStateID()); }
	void		OnEnter() override { printf_s("state_id : %d ) BotAction_B::OnEnter()\n", GetControlStateID()); }
	void		OnExit() override {
		printf_s("state_id : %d ) BotAction_B::OnExit()\n", GetControlStateID());
	//	controller_->AttachAction(new BotAction_B(GetControlStateID() + 2));
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

