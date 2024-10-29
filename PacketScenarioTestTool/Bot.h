#pragma once
#include "BotController.h"


typedef int BOT_ID;

class Bot
{
public:
	Bot() = default;
	Bot(BOT_ID id);

public:
	ControlState::EStatus Update(DWORD tick_diff);

public:
	bool PushAction(ACTION_TYPE action_type, void* value_ptr = nullptr);

	BOT_ID GetId() { return id_; }

	void LogIn() { is_login_ = true; }
	bool IsLogIn() { return is_login_; }
private:
	const BOT_ID id_;

	bool is_login_ = false;

	BotController controller_;
};

