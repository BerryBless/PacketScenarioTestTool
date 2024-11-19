#pragma once
//-------------------------------------------------------------------------------------------------------------
// 봇 클레스
//-------------------------------------------------------------------------------------------------------------
#include "BotController.h"
#include "GameClient.h"

typedef int BOT_ID;

class Bot
{
public:
	Bot() = default;
	Bot(BOT_ID id);

public:
	// 이 봇 업에이트
	ControlState::EStatus Update(DWORD tick_diff);

public:
	// 봇에 엑션큐에 엑션 넣기
	bool PushAction(ActionType ActionType, void* value_ptr = nullptr);

	BOT_ID GetId() { return id_; }

	// 로그인 체크
	void LogIn() { is_login_ = true; }
	bool IsLogIn() { return is_login_; }

	// 봇의 현재 엑션
	ActionType GetCurrentAction() { return controller_.GetCurrentAction(); }

	// 이 봇에 컨트롤 이벤트 보내기
	void OnActionEvent(BotControlEvent* control_event);
private:
	const BOT_ID id_;

	bool is_login_ = false;

	BotController controller_;
	GameClient game_client_;
};

