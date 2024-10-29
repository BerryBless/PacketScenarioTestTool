#include "pch.h"
#include "BotControlActionFactory.h"
#include "BotControlAction.h"

BotControlState* BotControlActionFactory::CreateState(ACTION_TYPE id)
{
	BotControlState* control_state = nullptr;
	
	switch (id)
	{
	case ACTION_TYPE::LogIn:		control_state = new BotAction_LogIn();		break;
	case ACTION_TYPE::Action_A:		control_state = new BotAction_A();		break;
	case ACTION_TYPE::Action_B:		control_state = new BotAction_B();		break;
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
