#include "pch.h"
#include "Bot.h"

Bot::Bot(BOT_ID id) :
	id_(id)
{
	controller_.Create(this);
	game_client_.Create(this);
}

ControlState::EStatus Bot::Update(DWORD tick_diff)
{
	// 네트워크 업데이트
	game_client_.Update(tick_diff);

	// 컨트롤러 업데이트
	return controller_.OnUpdate(tick_diff);
}

bool Bot::PushAction(ActionType ActionType, void* value_ptr)
{
	controller_.AttachAction(ActionType, value_ptr);
	return true;
}

void Bot::OnActionEvent(BotControlEvent* control_event)
{
	controller_.OnActionEvent(control_event);
}
