#include "Main.h"
#include "ControlEventReceiver.h"

int main()
{
	BotController test;

	test.OnEnter();
	test.AttachAction(ACTION_NODE_TYPE::Action_A);

	int cnt = 0;
	while (true)
	{
		if (cnt % 2 == 0)
		{
			test.OnActionEvent(new BotControlEvent_Action_A_2(cnt));
		}
		if (cnt % 5 == 0)
		{
			test.OnActionEvent(new BotControlEvent_Action_A_1("hello event"));
		}
		ControlState::EStatus status =  test.OnUpdate(1);
		if(status == ControlState::EStatus::Completed || status == ControlState::EStatus::Failed)
			break;
		++cnt;
	}

	test.OnExit();

	return 0;
}
