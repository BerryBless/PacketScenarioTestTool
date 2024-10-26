#include "BotControlAction.h"
#include "BotController.h"

void BotAction_A::OnExit()
{
	printf_s("state_id : %d ) BotAction_A::OnExit()\n", GetControlStateID());
}

ControlState::EStatus BotAction_A::OnUpdate(DWORD tick_diff)
{
	Sleep(100);
	printf_s("state_id : %d ) BotAction_A::OnUpdate() count = %d\n", GetControlStateID(), cnt);
	if (cnt >= 10)
	{
		SetStatus(ControlState::EStatus::Completed);
	}
	++cnt;
	return GetStatus();
}

ControlState::EStatus BotAction_A::OnActionEvent(BotControlEvent* control_event)
{
	if (control_event == nullptr)
	{
		return ControlState::EStatus::SystemError;
	}

	switch (control_event->GetEventType())
	{
	case ACTION_EVENT_TYPE::Action_A_1:
		OnEventAction_A_1(static_cast<BotControlEvent_Action_A_1*> (control_event));
		break;
	case ACTION_EVENT_TYPE::Action_A_2:
		OnEventAction_A_2(static_cast<BotControlEvent_Action_A_2*> (control_event));
		break;
	default:
		break;
	}

	return GetStatus();
}

void BotAction_A::OnEventAction_A_1(BotControlEvent_Action_A_1* control_event)
{
	if (control_event == nullptr)
	{
		SetStatus(ControlState::EStatus::SystemError);
		return ;
	}

	printf_s("OnEventAction_A_1)  %s\n", control_event->event_content_);
}

void BotAction_A::OnEventAction_A_2(BotControlEvent_Action_A_2* control_event)
{
	if (control_event == nullptr)
	{
		SetStatus(ControlState::EStatus::SystemError);
		return;
	}

	printf_s("OnEventAction_A_2)  %d\n", control_event->event_content_);
}
