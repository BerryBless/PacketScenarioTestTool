#pragma once
//-------------------------------------------------------------------------------------------------------------
// ControlState
// 상태를 갖는 행동 (엑션)
//-------------------------------------------------------------------------------------------------------------

class ControlState
{
public:
	typedef int ControlStateID;
	static const ControlStateID Invalid_ControlStateID = -1;



	enum class EStatus : BYTE
	{
		NotReady,		// 준비 되지 않음. 강제로 시작시켜줘야함,
		Activated,		// 진행중
		Inactivated,	// 진행중지
		Completed,		// 진행완료
		Failed,			// 진행실패
		Changed,		// 상태 변경시
		Blocked,		// block 상태, event 로 ACTIVATED, COMPLETED, FAILED등으로 변경 가능하다.
		SystemError,	// system error, 더이상 진행하지 않는다.

		Max,
		Invalid = 0xff,
	};


	typedef int EventId;
	static const EventId Invalid_EventId = -1;

	class ControlEvent
	{
	public:
		ControlEvent(EventId eventId) : id(eventId) {}
		virtual ~ControlEvent() {}
		EventId id = Invalid_EventId;
	};

public:
	ControlState(ControlStateID control_state_id)
		: control_state_id_(control_state_id)
	{}

	virtual ~ControlState();


public:
	// 생성
	virtual void	OnEnter() {}
	// 삭제
	virtual void	OnExit() {}
	// 업데이트
	virtual EStatus	OnUpdate(DWORD tick_diff);

public:
	// 서브컨트롤 추가

	// 이벤트 발생
	virtual EStatus	OnEvent(ControlEvent* control_event);


public:
	// 서브컨트롤 
	virtual bool	AddToSubControl(ControlState* control_state);
	EStatus			UpdateSubControl(DWORD tick_diff);
	void			RemoveAllSubControl();

public:
	ControlState*	GetParent() { return parent_; }
	void			SetParent(ControlState* pParent) { parent_ = pParent; }

	void			SetStatus(EStatus status) { status_ = status; }
	EStatus			GetStatus() { return status_; }
	bool			IsStatus(EStatus status) const { return (status_ == status) ? true : false; }

	int				GetControlStateID() { return control_state_id_; }
	const char*		GetControlStateName() { return control_state_name_; }

	// **사용시 할당, 해지 주의**
	// 임시로 만들어둠
	void			SetVarablePtr(void* variable_ptr) { SAFE_DELETE(variable_ptr_); variable_ptr_ = variable_ptr; }
	void*			GetVarablePtr() { return variable_ptr_; }


public:

	virtual void	Start() { if (IsStatus(EStatus::Inactivated)) { status_ = EStatus::Activated; OnEnter(); } }
	virtual void	Stop() { if ((IsStatus(EStatus::NotReady) || IsStatus(EStatus::Inactivated)) != true) { OnExit(); status_ = EStatus::Inactivated; } }

public:
	bool			IsEmpty() { return sub_control_.empty() == true; }

	int				GetDepth();

protected:
	EStatus status_ = EStatus::Inactivated;

	ControlState* parent_ = nullptr;

	ControlStateID	control_state_id_ = Invalid_EventId;
	const char* control_state_name_ = nullptr; 

	// 큐처럼 사용
	// TODO list로도 만들기
	std::list<ControlState*>	sub_control_;

	//  변수 저장용 ptr 
	// TODO 변수용으로 쓸 class 만들기
	void* variable_ptr_ = nullptr;
};

