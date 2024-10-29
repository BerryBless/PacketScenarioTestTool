#include "pch.h"
#include "BotControlActionFactory.h"
#include "BotControlAction.h"

BotControlState* BotControlActionFactory::CreateState(ActionType id)
{
	BotControlState* control_state = nullptr;
	
	switch (id)
	{
	case ActionType::LogIn:		control_state = new BotAction_LogIn();		break;
	case ActionType::Action_A:		control_state = new BotAction_A();		break;
	case ActionType::Action_B:		control_state = new BotAction_B();		break;
	default:
		LOG_ERROR("ERROR");
		break;
	}

	return control_state;
}

void BotControlActionFactory::DestoryState(BotControlState* state)
{
	SAFE_DELETE(state);
}
