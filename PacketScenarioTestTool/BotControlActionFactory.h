#pragma once

class BotControlState;

class BotControlActionFactory
{
public:
	BotControlActionFactory() {}
	virtual ~BotControlActionFactory() {}

	static BotControlState* CreateState(ACTION_TYPE id);
	static void DestoryState(BotControlState* state);

};

