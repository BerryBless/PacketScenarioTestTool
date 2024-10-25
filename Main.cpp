#include "Main.h"

int main()
{
	BotController test(1);

	test.OnEnter();
	test.AttachAction(10);
	while (true)
	{
		ControlState::EStatus status =  test.OnUpdate(1);
		if(status == ControlState::EStatus::Completed || status == ControlState::EStatus::Failed)
			break;
	}

	test.OnExit();

	return 0;
}
