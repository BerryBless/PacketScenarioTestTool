#include "pch.h"
#include "Bot.h"

Bot::Bot(BOT_ID id) :
	id_(id)
{
	controller_.Create(this);
}

void Bot::Update(DWORD tick_diff)
{
	controller_.OnUpdate(tick_diff);
}

bool Bot::PushAction(ACTION_TYPE action_type, void* value_ptr)
{
	controller_.AttachAction(action_type, value_ptr);
	return true;
}
