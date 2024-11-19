#pragma once
//-------------------------------------------------------------------------------------------------------------
// 액션 생성 펙토리
//-------------------------------------------------------------------------------------------------------------
#include "ActionDefine.h"
class BotControlState;

class BotControlActionFactory
{
public:
	BotControlActionFactory() {}
	virtual ~BotControlActionFactory() {}

	// action_type에 맞는 엑션 생성
	static BotControlState* CreateState(ActionType action_type);
	// 생성된 엑션을 소멸
	static void DestoryState(BotControlState* state);

};

