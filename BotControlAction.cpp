#include "BotControlAction.h"
#include "BotController.h"

void BotAction_A::OnExit()
{
	printf_s("state_id : %d ) BotAction_A::OnExit()\n", GetControlStateID());
}