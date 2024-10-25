#include "Main.h"

int main()
{
	BotController test;

	test.OnEnter();
	test.AttachAction(ACTION_NODE_TYPE::Action_A);
	test.AttachAction(ACTION_NODE_TYPE::Action_B);
	test.AttachAction(ACTION_NODE_TYPE::Action_A);

	while (true)
	{
		ControlState::EStatus status =  test.OnUpdate(1);
		if(status == ControlState::EStatus::Completed || status == ControlState::EStatus::Failed)
			break;
	}

	test.OnExit();

	return 0;
}
