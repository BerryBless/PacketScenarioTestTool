#include "BotController.h"

void BotController::AttachAction(ACTION_ID id)
{
	AttachNode(this, id);
}
