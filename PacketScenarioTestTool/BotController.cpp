#include "pch.h"
#include "BotController.h"
#include "Bot.h"

void BotController::Create(Bot* owner)
{
	owner_bot_ = owner;
}

void BotController::AttachAction(ACTION_TYPE id, void* value_ptr)
{
	AttachNode(this, id, value_ptr);
}

void BotController::OnActionEvent(BotControlEvent* control_event)
{
	OnEvent(control_event);
	SAFE_DELETE(control_event);
}
