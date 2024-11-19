#pragma once
#include "BotControlState.h"
#include "ControlEventReceiver.h"

//-------------------------------------------------------------------------------------------------------------
// 엑션 템플릿 만들기
//-------------------------------------------------------------------------------------------------------------
class BotControlAction : public BotControlState
{
public:
	BotControlAction(ActionType node_type) : BotControlState(node_type) {}
};


template<ActionType TNodeType>
class TBotControlAction : public BotControlAction
{
public:
	TBotControlAction() : BotControlAction(TNodeType) {}


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
class BotAction_A : public TBotControlAction<ActionType::Action_A>
{

public:
	// 시작 준비
	void		OnAttached() override;
	// 소멸 할때
	void		OnDetached() override;

	// 시작 할때
	void		OnEnter() override;
	// 끝날때
	void		OnExit() override;
	// 업에이트
	EStatus		OnUpdate(DWORD tick_diff) override;
	// 엑션에 이벤트가 올때
	EStatus		OnActionEvent(BotControlEvent* control_event) override;

private:
	// 이벤트 A_1가 왔을때 OnActionEvent에서 호출
	void		OnEventAction_A_1(BotControlEvent_Action_A_1* control_event);
	// 이벤트 A_2가 왔을때 OnActionEvent에서 호출
	void		OnEventAction_A_2(BotControlEvent_Action_A_2* control_event);

private:
	// 업데이트 테스트용 변수
	int cnt = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_B
///////////////////////////////////////////////////////////////////////////////////////////
class BotAction_B : public TBotControlAction<ActionType::Action_B>
{

public:
	void		OnAttached() override;
	void		OnDetached() override;
	void		OnEnter() override;
	void		OnExit() override;
	EStatus		OnUpdate(DWORD tick_diff) override;
	EStatus		OnActionEvent(BotControlEvent* control_event) override;


private:
	int cnt = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_LogIn
///////////////////////////////////////////////////////////////////////////////////////////
class BotAction_LogIn : public TBotControlAction<ActionType::LogIn>
{

public:
	void		OnAttached() override;
	void		OnDetached() override;
	void		OnEnter() override;
	void		OnExit() override;
	EStatus		OnUpdate(DWORD tick_diff) override;
	EStatus		OnActionEvent(BotControlEvent* control_event) override;

private:
	// 이벤트

private:
	int cnt = 0;
};
