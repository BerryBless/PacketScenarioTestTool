#include "pch.h"
#include "BotControlAction.h"
#include "BotController.h"
#include "Bot.h"
void BotAction_A::OnAttached()
{
	LOG_INFO("bot_id : {} ) BotAction_A::OnAttached(), Depth {}\n", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_A::OnExit()
{
	LOG_INFO("bot_id : {} ) BotAction_A::OnExit()\n", controller_->GetOwner()->GetId());
}

ControlState::EStatus BotAction_A::OnUpdate(DWORD tick_diff)
{
	LOG_INFO("bot_id : {} ) BotAction_A::OnUpdate() count = %d\n", controller_->GetOwner()->GetId(), cnt);
// 	if (cnt >= 10)
// 	{
// 		SetStatus(ControlState::EStatus::Completed);
// 	}
// 	++cnt;
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

	LOG_INFO("OnEventAction_A_1)  {}\n", control_event->event_content_.c_str());
}

void BotAction_A::OnEventAction_A_2(BotControlEvent_Action_A_2* control_event)
{
	if (control_event == nullptr)
	{
		SetStatus(ControlState::EStatus::SystemError);
		return;
	}

	LOG_INFO("OnEventAction_A_2)  {}\n", control_event->event_content_);
}
