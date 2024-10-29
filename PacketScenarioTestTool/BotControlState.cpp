#include "pch.h"
#include "BotControlState.h"
#include "BotController.h"
#include "BotControlActionFactory.h"

void BotControlState::Stop()
{
	if (controller_ != nullptr)
	{
		OnDetached();
	}
	__super::Stop();
}

bool BotControlState::AddToSubControl(ControlState* control_state)
{
	if (control_state == nullptr)
	{
		LOG_ERROR("AddToSubControl control_state == nullptr");
		SetStatus(ControlState::EStatus::SystemError);

		return false;
	}

    bool result = __super::AddToSubControl(control_state);
    static_cast<BotControlState*>(control_state)->OnAttached();

    return true;
}

bool BotControlState::AttachNode(BotController* controller, ACTION_TYPE id, void* value_ptr, bool attach_action)
{

	if (controller == nullptr)
	{
		LOG_ERROR("AddToSubControl controller == nullptr");
		SetStatus(ControlState::EStatus::SystemError);
		return false;
	}

	controller_ = controller;

	// 자식 붙이기
	if (attach_action)
	{
		if (AttachSubAction(id, value_ptr) == false)
		{
			return false;
		}
	}

	return true;
}

bool BotControlState::AttachSubAction(ACTION_TYPE id, void* value_ptr)
{
 	BotControlState* next_action = BotControlActionFactory::CreateState(id);
 	
 	if (next_action->AttachNode(controller_, id,  value_ptr, false) == false)
 	{
		BotControlActionFactory::DestoryState(next_action);
 		return false;
 	}
 
 	if (AddToSubControl(next_action) == false)
 	{
		BotControlActionFactory::DestoryState(next_action);
 		return false;
 	}
	
	next_action->SetVarablePtr(value_ptr);
	
	return true;
}
