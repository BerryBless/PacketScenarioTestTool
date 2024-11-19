# PacketScenarioTestTool

Bot이 각 Action을 가지고 있고, 이 Action의 조합으로 서버를 테스트 하는 툴입니다.


![image](https://github.com/user-attachments/assets/8aa4b182-e6dc-46fd-980e-0c92fad9968f)

테스트 하고 싶은 시나리오를 BotControlAction을 상속 받아 TestAction을 만들고
BotController에 등록하여 해당 Action을 실행하도록 설계했습니다.


사용법

엑션(테스트 시나리오) 추가
1. ActionType에 Action_A 타입 추가

ActionDefine.h
```
enum class ActionType
{
	...
	Action_A, // 액션 A
 ...
};
```

2. BotControlAction.h 에 BotAction_A 클레스 작성

```
///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_A
///////////////////////////////////////////////////////////////////////////////////////////
class BotAction_A : public TBotControlAction<ActionType::Action_A>
{

public:
	// 시작 준비
	void		OnAttached() override;
	// 소멸 할때
	void		OnDetached() override;

	// 시작 할때
	void		OnEnter() override;
	// 끝날때
	void		OnExit() override;
	// 업에이트
	EStatus		OnUpdate(DWORD tick_diff) override;
	// 엑션에 이벤트가 올때
	EStatus		OnActionEvent(BotControlEvent* control_event) override;

};

```

3. BotControlActionFactory::CreateState 에 ActionType::Action_A과 BotAction_A 클레스 이어주기
BotControlActionFactory.cpp
```
BotControlState* BotControlActionFactory::CreateState(ActionType action_type)
{
	BotControlState* control_state = nullptr;
	
	switch (action_type)
	{
 ...
	case ActionType::Action_A:		control_state = new BotAction_A();		break;
 ...
	}

	return control_state;
}
```

이벤트 추가
1. ActionEventType에 Action_A에서 일어날 이벤트 A_Event_1 추가
ActionDefine.h
```
enum class ActionEventType
{
...
	A_Event_1,
...
};

```

2. ControlEventReceiver에서 A_Event_1가 일어날때 필요한 데이터 클레스 작성

```
///////////////////////////////////////////////////////////////////////////////////////////
// BotControlEvent_A_Event_1
///////////////////////////////////////////////////////////////////////////////////////////
class BotControlEvent_A_Event_1 : public TBotControllEvent<ActionEventType::A_Event_1>
{
public:
	BotControlEvent_A_Event_1(std::string event_content) :
		event_content_(event_content){}

public:
	const std::string event_content_;
};
```

3. BotAction_A 클레스에서 OnEventA_Event_1(BotControlEvent_A_Event_1* control_event)작성후 OnActionEvent() 메소드 수정

BotControlAction.h
```
///////////////////////////////////////////////////////////////////////////////////////////
// BotAction_A
///////////////////////////////////////////////////////////////////////////////////////////
class BotAction_A : public TBotControlAction<ActionType::Action_A>
{
...
	// 엑션에 이벤트가 올때
	EStatus		OnActionEvent(BotControlEvent* control_event) override;

private:
	// 이벤트 A_1가 왔을때 OnActionEvent에서 호출
	void		OnEventA_Event_1(BotControlEvent_A_Event_1* control_event);

...
};

```

BotControlAction.cpp
```
ControlState::EStatus BotAction_A::OnActionEvent(BotControlEvent* control_event)
{
...
	switch (control_event->GetEventType())
	{
...
// 추가
	case ActionEventType::A_Event_1:
		OnEventA_Event_1(static_cast<BotControlEvent_A_Event_1*> (control_event));
		break;
...
	}
...
}

void BotAction_A::OnEventA_Event_1(BotControlEvent_A_Event_1* control_event)
{
	if (control_event == nullptr)
	{
		SetStatus(ControlState::EStatus::SystemError);
		return ;
	}

	LOG_DEBUG("OnEventA_Event_1)  {}", control_event->event_content_.c_str());


	SetStatus(ControlState::EStatus::Activated);
}
```


 테스트 진행시 실행 순서
 1. 설정 파일 Test.json를 불러와 테스트할 action_list 를 불러옴
 2. 봇을 스레드마다 균등하게 분배해 생성
 3. 생성할 봇마다 action_list을 넣고 실행
