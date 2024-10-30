#pragma once
#include "ActionDefine.h"
class BotControlState;

class BotControlActionFactory
{
public:
	BotControlActionFactory() {}
	virtual ~BotControlActionFactory() {}

	static BotControlState* CreateState(ActionType id);
	static void DestoryState(BotControlState* state);

};

