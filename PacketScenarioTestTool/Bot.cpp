#include "pch.h"
#include "Bot.h"

Bot::Bot(BOT_ID id) :
	id_(id)
{
	controller_.Create(this);
}

ControlState::EStatus Bot::Update(DWORD tick_diff)
{
	// TODO 네트워크 업데이트

	return controller_.OnUpdate(tick_diff);
}

bool Bot::PushAction(ACTION_TYPE action_type, void* value_ptr)
{
	controller_.AttachAction(action_type, value_ptr);
	return true;
}
