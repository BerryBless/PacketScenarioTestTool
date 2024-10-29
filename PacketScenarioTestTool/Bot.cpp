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

bool Bot::PushAction(ActionType ActionType, void* value_ptr)
{
	controller_.AttachAction(ActionType, value_ptr);
	return true;
}
