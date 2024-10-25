#pragma once
#include "pch.h"
#include "ControlState.h"
#include "BotControlState.h"

class BotController : public BotControlState
{
public:
	BotController(ControlStateID control_state_id) : BotControlState(control_state_id) {}

public:
	// 상속
	void	OnEnter() override { std::cout << "BotController::OnEnter()"; }
	void	OnExit() override { std::cout << "BotController::OnExit()"; }
	//EStatus	OnUpdate(DWORD tick_diff) override;
	//EStatus	OnEvent(ControlEvent* control_event) override;
	//void	Start() override { __super::Start(); }
	//void	Stop() override { __super::Stop(); }


public:

	// 컨트롤러에 다음 액션 추가
	void AttachAction(ACTION_ID id);
};

