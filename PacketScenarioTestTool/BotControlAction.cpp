#include "pch.h"
#include "BotControlAction.h"
#include "BotController.h"
#include "Bot.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BotAction_A
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BotAction_A::OnAttached()
{
	LOG_DEBUG("bot_id : {} ) BotAction_A::OnAttached(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_A::OnDetached()
{
	LOG_DEBUG("bot_id : {} ) BotAction_A::OnDetached(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_A::OnEnter()
{
	LOG_DEBUG("bot_id : {} ) BotAction_A::OnEnter(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());

	SetStatus(ControlState::EStatus::Blocked);
}

void BotAction_A::OnExit()
{
	LOG_DEBUG("bot_id : {} ) BotAction_A::OnExit()", controller_->GetOwner()->GetId());
}
ControlState::EStatus BotAction_A::OnUpdate(DWORD tick_diff)
{
	LOG_DEBUG("bot_id : {} ) BotAction_A::OnUpdate() count = {}", controller_->GetOwner()->GetId(), cnt);
 	if (cnt >= 10)
 	{
		LOG_DEBUG("bot_id : {} ) BotAction_A::OnUpdate() Completed", controller_->GetOwner()->GetId());
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
	case ActionEventType::Action_A_1:
		OnEventAction_A_1(static_cast<BotControlEvent_Action_A_1*> (control_event));
		break;
	case ActionEventType::Action_A_2:
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

	LOG_DEBUG("OnEventAction_A_1)  {}", control_event->event_content_.c_str());


	SetStatus(ControlState::EStatus::Activated);
}

void BotAction_A::OnEventAction_A_2(BotControlEvent_Action_A_2* control_event)
{
	if (control_event == nullptr)
	{
		SetStatus(ControlState::EStatus::SystemError);
		return;
	}

	LOG_DEBUG("OnEventAction_A_2)  {}", control_event->event_content_);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BotAction_B
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BotAction_B::OnAttached()
{
	LOG_DEBUG("bot_id : {} ) BotAction_B::OnAttached(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_B::OnDetached()
{
	LOG_DEBUG("bot_id : {} ) BotAction_B::OnDetached(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_B::OnEnter()
{
	LOG_DEBUG("bot_id : {} ) BotAction_B::OnEnter(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_B::OnExit()
{
	LOG_DEBUG("bot_id : {} ) BotAction_B::OnExit()", controller_->GetOwner()->GetId());
}

ControlState::EStatus BotAction_B::OnUpdate(DWORD tick_diff)
{
	LOG_DEBUG("bot_id : {} ) BotAction_B::OnUpdate() count = {}", controller_->GetOwner()->GetId(), cnt);
	if (cnt >= 10)
	{
		SetStatus(ControlState::EStatus::Completed);
	}
	++cnt;
	return GetStatus();
}

ControlState::EStatus BotAction_B::OnActionEvent(BotControlEvent* control_event)
{
	if (control_event == nullptr)
	{
		return ControlState::EStatus::SystemError;
	}

	switch (control_event->GetEventType())
	{
	case ActionEventType::Action_A_1:
		//OnEventAction_A_1(static_cast<BotControlEvent_Action_A_1*> (control_event));
		break;
	case ActionEventType::Action_A_2:
		//OnEventAction_A_2(static_cast<BotControlEvent_Action_A_2*> (control_event));
		break;
	default:
		break;
	}

	return GetStatus();
}

///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_LogIn
///////////////////////////////////////////////////////////////////////////////////////////
void BotAction_LogIn::OnAttached()
{
	LOG_DEBUG("bot_id : {} ) BotAction_LogIn::OnAttached(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());

	if (controller_->GetOwner()->IsLogIn())
	{
		SetStatus(ControlState::EStatus::Completed);
	}

}

void BotAction_LogIn::OnDetached()
{
	LOG_DEBUG("bot_id : {} ) BotAction_LogIn::OnDetached(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_LogIn::OnEnter()
{
	LOG_DEBUG("bot_id : {} ) BotAction_LogIn::OnEnter(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
}

void BotAction_LogIn::OnExit()
{
	LOG_DEBUG("bot_id : {} ) BotAction_LogIn::OnExit(), Depth {}", controller_->GetOwner()->GetId(), GetDepth());
	controller_->GetOwner()->LogIn();
}

ControlState::EStatus BotAction_LogIn::OnUpdate(DWORD tick_diff)
{
	LOG_DEBUG("bot_id : {} ) BotAction_LogIn::OnUpdate() count = %d", controller_->GetOwner()->GetId(), cnt);
	if (cnt >= 10)
	{
		SetStatus(ControlState::EStatus::Completed);
	}
	++cnt;
	return GetStatus();
}

ControlState::EStatus BotAction_LogIn::OnActionEvent(BotControlEvent* control_event)
{
	if (control_event == nullptr)
	{
		return ControlState::EStatus::SystemError;
	}

	switch (control_event->GetEventType())
	{
	case ActionEventType::Action_A_1:
		//OnEventAction_A_1(static_cast<BotControlEvent_Action_A_1*> (control_event));
		break;
	case ActionEventType::Action_A_2:
		//OnEventAction_A_2(static_cast<BotControlEvent_Action_A_2*> (control_event));
		break;
	default:
		break;
	}

	return GetStatus();
}
