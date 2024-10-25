#pragma once
#include "pch.h"
#include "ControlState.h"
#include "BotControlState.h"

class BotController : public BotControlState
{
public:
	BotController(ControlStateID control_state_id) : BotControlState(control_state_id) {}

public:
	// »ó¼Ó
	void	OnEnter() override { std::cout << "BotController::OnEnter()"; }
	void	OnExit() override { std::cout << "BotController::OnExit()"; }
	//EStatus	OnUpdate(DWORD tick_diff) override;
	//EStatus	OnEvent(ControlEvent* control_event) override;
	//void	Start() override { __super::Start(); }
	//void	Stop() override { __super::Stop(); }


public:
	void AttachAction(ACTION_ID id);
};

