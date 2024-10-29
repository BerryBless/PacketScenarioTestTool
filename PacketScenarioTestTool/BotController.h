#pragma once
#include "ControlState.h"
#include "BotControlState.h"
#include "ControlEventReceiver.h"

class Bot;

class BotController : public BotControlState
{
public:
	BotController() : BotControlState(ACTION_TYPE::Controller) {}

public:
	// 상속
	void	OnEnter() override { std::cout << "BotController::OnEnter()"; }
	void	OnExit() override { std::cout << "BotController::OnExit()"; }
	//EStatus	OnUpdate(DWORD tick_diff) override;
	//EStatus	OnEvent(ControlEvent* control_event) override;
	//void	Start() override { __super::Start(); }
	//void	Stop() override { __super::Stop(); }


public:
	void Create(Bot* owner_bot);

	// 컨트롤러에 다음 액션 추가
	void AttachAction(ACTION_TYPE id, void* value_ptr = nullptr);

	// 컨트롤러에 붙어있는 모든 엑션에 대헤 이벤트 실행
	// new BotControlEvent 해서 넣어주면 안에서 삭제, 1회용 
	void OnActionEvent(BotControlEvent* control_event);


	Bot* GetOwner()  { return owner_bot_; }
protected:
	Bot* owner_bot_ = nullptr;
};

