#include "BotController.h"

void BotController::AttachAction(ACTION_NODE_TYPE id)
{
	AttachNode(this, id);
}

void BotController::OnActionEvent(BotControlEvent* control_event)
{
	OnEvent(control_event);
	SAFE_DELETE(control_event);
}
