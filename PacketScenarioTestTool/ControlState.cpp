#include "pch.h"
#include "ControlState.h"

ControlState::~ControlState()
{
	RemoveAllSubControl();
	SAFE_DELETE(variable_ptr_);
}
////////////////////////////////////////////////////////////////////////////////////////
// OnUpdate
////////////////////////////////////////////////////////////////////////////////////////
ControlState::EStatus ControlState::OnUpdate(DWORD tick_diff)
{
	EStatus status = EStatus::Invalid;

	status = UpdateSubControl(tick_diff);
	if (status == EStatus::Changed)
	{
		return EStatus::Changed;
	}

	return status;
}

////////////////////////////////////////////////////////////////////////////////////////
// OnEvent
////////////////////////////////////////////////////////////////////////////////////////
ControlState::EStatus ControlState::OnEvent(ControlEvent* control_event)
{
	if (control_event == nullptr)
	{
		LOG_ERROR("OnEvent  control_event == nullptr");
		return EStatus::SystemError;
	}

	if(sub_control_.empty())
		return EStatus::Completed;


// Sub Control 리스트 순회하며 이벤트 적용 할때
// 	for (auto sub_control_iter = sub_control_.begin(); sub_control_iter != sub_control_.end(); ++sub_control_iter)
// 	{
// 		if (EStatus::Activated == sub_control_iter->GetStatus() || EStatus::Blocked == sub_control_iter->GetStatus())
// 		{
// 			sub_control_iter->OnEvent(control_event);
// 		}
// 	}

	// 큐처럼 쓸때
	auto sub_control_iter = sub_control_.begin();

	return (*sub_control_iter)->OnEvent(control_event);
}

////////////////////////////////////////////////////////////////////////////////////////
// AddToSubControl
////////////////////////////////////////////////////////////////////////////////////////
bool ControlState::AddToSubControl(ControlState* control_state)
{
	if (control_state == nullptr)
	{
		LOG_ERROR("AddToSubControl  control_state == nullptr");
		SetStatus(ControlState::EStatus::SystemError);
		return false;
	}

	control_state->SetParent(this);
	sub_control_.push_back(control_state);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
// UpdateSubControl
////////////////////////////////////////////////////////////////////////////////////////
ControlState::EStatus ControlState::UpdateSubControl(DWORD tick_diff)
{
	if (sub_control_.empty())
		return EStatus::Completed;

	auto sub_control_iter = sub_control_.begin();
	// 첫 서브컨트롤이 완료되었는지 확인
	while (sub_control_iter != sub_control_.end())
	{
		ControlState* sub_control_ptr = nullptr;
		sub_control_ptr = (*sub_control_iter);
		if (sub_control_ptr == nullptr)
		{
			// 비어있는데 큐에 들어가있다??
			LOG_ERROR("UpdateSubControl  sub_control_ptr == nullptr");
			break;
		}

		if (sub_control_ptr->IsStatus(EStatus::Completed) || sub_control_ptr->IsStatus(EStatus::Failed))
		{
			// 서브 컨트롤 완료
			// 종료 처리후 free
			sub_control_ptr->Stop();
			SAFE_DELETE(sub_control_ptr);
			sub_control_iter = sub_control_.erase(sub_control_iter);
		}
		
		break;
	}


	if (sub_control_iter == sub_control_.end())
		return EStatus::Completed;


	// 시작
	(*sub_control_iter)->Start();

	EStatus status = (*sub_control_iter)->GetStatus();
	switch (status)
	{
	case ControlState::EStatus::Activated:
		// 순항중~~
		break;
	case ControlState::EStatus::Completed:
	case ControlState::EStatus::Failed:
		// 완료된 상태
	{
		ControlState* sub_control_ptr = nullptr;
		sub_control_ptr = (*sub_control_iter);

		// 종료 처리후 free
		sub_control_ptr->Stop();
		SAFE_DELETE(sub_control_ptr);
		sub_control_iter = sub_control_.erase(sub_control_iter);

		if (sub_control_.empty() == false)
		{
			// 다음 서브컨트롤이 있는경우
			return EStatus::Activated;
		}
	}
		return status;
	case ControlState::EStatus::Changed:
		// Update 말고 다른곳에서 바꾸라고 한경우 (Event 라든가..)
		return EStatus::Changed;
	
	// 진행하면 안되는것들
	case ControlState::EStatus::NotReady:
	case ControlState::EStatus::Blocked:
	case ControlState::EStatus::SystemError:
		return status;
	default:
		// 올수 없는경우
		LOG_ERROR("default");
		return EStatus::SystemError;
	}


	// 업데이트
	status = (*sub_control_iter)->OnUpdate(tick_diff);
	switch (status)
	{
	case ControlState::EStatus::NotReady:
		// 업데이트는 이상태가 되면 안된다 시작부터 해야함
		break;
	case ControlState::EStatus::Activated:
		break;
	case ControlState::EStatus::Completed:
	case ControlState::EStatus::Failed:
		// 완료된 상태
	{
		ControlState* sub_control_ptr = nullptr;
		sub_control_ptr = (*sub_control_iter);

		// 종료 처리후 free
		sub_control_ptr->Stop();
		SAFE_DELETE(sub_control_ptr);
		sub_control_iter = sub_control_.erase(sub_control_iter);

		if (sub_control_.empty() == false)
		{
			// 다음 서브컨트롤이 있는경우
			return EStatus::Activated;
		}
	}
	return status;
	case ControlState::EStatus::Changed:
	{
		(*sub_control_iter)->Stop();
	}
	return EStatus::Changed;

	case ControlState::EStatus::Blocked:
	case ControlState::EStatus::SystemError:
		break;
	default:
		// 올수 없는경우
		LOG_ERROR("default");
		return EStatus::SystemError;
	}

	return status;
}

////////////////////////////////////////////////////////////////////////////////////////
// RemoveAllSubControl
////////////////////////////////////////////////////////////////////////////////////////
void ControlState::RemoveAllSubControl()
{
	auto iter = sub_control_.begin();
	while (iter != sub_control_.end())
	{
		(*iter)->Stop();
		SAFE_DELETE((*iter));
		iter = sub_control_.erase(iter);
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// GetDepth
////////////////////////////////////////////////////////////////////////////////////////
int ControlState::GetDepth()
{
	int depth = 0;
	ControlState* parent = parent_;
	while (parent != nullptr)
	{
		++depth;
		parent = parent->GetParent();
	}
	return depth;
}
