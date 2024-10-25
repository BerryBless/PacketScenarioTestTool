#include "Main.h"

#include "BotControllAction.h"

int main()
{
	BotController test(1);

	test.OnEnter();
	test.AddToSubControl(new BotAction_A(1));
	test.AddToSubControl(new BotAction_B(2));

	while (true)
	{
		ControlState::EStatus status =  test.OnUpdate(1);
		if(status == ControlState::EStatus::Completed || status == ControlState::EStatus::Failed)
			break;
	}

	test.OnExit();

	return 0;
}
