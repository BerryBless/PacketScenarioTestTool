#pragma once

//=================================================================================
// 사용할 네트워크 라이브러리의 클라이언트 부분을 넣기
// 
//=================================================================================

class ClientBase
{
public:
	virtual void Update(DWORD tick_diff) = 0;
	virtual bool Connect(const std::string& ip, int port) = 0;
	virtual void Disconnect() ;

};

