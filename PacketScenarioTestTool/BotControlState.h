#pragma once
#include "ControlState.h"

class BotController;

class BotControlState : public ControlState
{
public:
	BotControlState(ActionType state_node) : ControlState(static_cast<ControlStateID>(state_node)){}

	// 상속
	void			Start() override;
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
	// 컨트롤러에 이 노드 넣기
	virtual bool AttachNode(BotController* controller, ActionType id, void* value_ptr, bool attach_action = true);
	// 서브 엑션 추가
	bool AttachSubAction(ActionType id, void* value_ptr);

	ActionType GetActionType() { return static_cast<ActionType>(GetControlStateID()); }
protected:

	BotController* controller_ = nullptr;
private:

};

