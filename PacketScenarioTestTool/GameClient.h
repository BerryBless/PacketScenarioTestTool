#pragma once
#include "ClientBase.h"

class Bot;

class GameClient : public ClientBase
{
public:

	void Update(DWORD tick_diff) override;
	bool Connect(const std::string& ip, int port) override;
	void Disconnect() override;

public:
	void Create(Bot* owner);
private:
	// 더미용
	int count = 0;

	Bot* owner_bot_ = nullptr;
};

