#pragma once
class ClientBase
{
public:
	virtual void Update(DWORD tick_diff) = 0;
	virtual bool Connect(const std::string& ip, int port) = 0;
	virtual void Disconnect() ;

};

