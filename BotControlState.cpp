#include "BotControlState.h"
#include "BotController.h"

void BotControlState::Stop()
{
	if (controller_ != nullptr)
	{
		OnDetached();
	}
	__super::Stop();
}

bool BotControlState::AddToSubControl(ControlState* control_state)
{
    bool result = __super::AddToSubControl(control_state);
    static_cast<BotControlState*>(control_state)->OnAttached();

    return false;
}
