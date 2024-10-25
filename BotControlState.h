#pragma once
#include "pch.h"
#include "ControlState.h"

class BotController;

class BotControlState : public ControlState
{
public:
	BotControlState(ControlStateID control_state_id) : ControlState(control_state_id){}

	// 상속
	void			Stop() override;
	void			OnEnter() override { std::cout << "BotControlState::OnEnter()"; }
	void			OnExit() override { std::cout << "BotControlState::OnExit()"; }

	bool			AddToSubControl(ControlState* control_state) override;
public:
	BotController*	GetController() { return controller_; }

	// 컨트롤러에 붙힐때 호출
	virtual void	OnAttached() {}
	// 컨트롤러에 삭제할때 호출
	virtual void	OnDetached() {}

public:

protected:

	BotController* controller_ = nullptr;
private:

};

