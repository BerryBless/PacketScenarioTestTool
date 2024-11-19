#pragma once
//-------------------------------------------------------------------------------------------------------------
// 게임서버와 연결할 클라이언트
// 사용할 네트워크 라이브러리에 맞게 수정필요!
//-------------------------------------------------------------------------------------------------------------
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

