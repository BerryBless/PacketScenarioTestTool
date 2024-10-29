#pragma once
#include "BotController.h"


typedef int BOT_ID;

class Bot
{
public:
	Bot() = default;
	Bot(BOT_ID id);

public:
	void Update(DWORD tick_diff);

public:
	bool PushAction(ACTION_TYPE action_type, void* value_ptr = nullptr);

	BOT_ID GetId() { return id_; }
private:
	const BOT_ID id_;

	BotController controller_;
};

