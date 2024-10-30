#include "pch.h"
#include "GameClient.h"
#include "Bot.h"


void GameClient::Create(Bot* owner)
{
	owner_bot_ = owner;
}

void GameClient::Update(DWORD tick_diff)
{
	count += tick_diff;
	if (count > 10000)
	{
		owner_bot_->OnActionEvent(new BotControlEvent_Action_A_1("test"));
		count = 0;
	}
}

bool GameClient::Connect(const std::string& ip, int port)
{
	return true;
}

void GameClient::Disconnect()
{
}