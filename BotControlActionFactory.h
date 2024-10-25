#pragma once
#include "pch.h"

class BotControlState;

class BotControlActionFactory
{
public:
	BotControlActionFactory() {}
	virtual ~BotControlActionFactory() {}

	static BotControlState* CreateState(ACTION_NODE_TYPE id);
	static void DestoryState(BotControlState* state);

};

