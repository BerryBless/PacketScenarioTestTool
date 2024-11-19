# PacketScenarioTestTool

Bot이 각 Action을 가지고 있고, 이 Action의 조합으로 서버를 테스트 하는 툴입니다.

[큰 구조]
![image](https://github.com/user-attachments/assets/8aa4b182-e6dc-46fd-980e-0c92fad9968f)

테스트 하고 싶은 시나리오를 BotControlAction을 상속 받아 TestAction을 만들고
BotController에 등록하여 해당 Action을 실행하도록 설계했습니다.


사용법.

엑션(테스트 시나리오) 추가
1. ActionType에 Action_A 타입 추가
2. BotControlAction.h 에 BotAction_A 클레스 작성
3. BotControlActionFactory::CreateState 에 ActionType::Action_A과 BotAction_A 클레스 이어주기


이벤트 추가
1. ActionEventType에 Action_A에서 일어날 이벤트 A_Event_1 추가
2. ControlEventReceiver에서 A_Event_1가 일어날때 필요한 데이터 클레스 작성
3. BotAction_A 클레스에서 OnEventA_Event_1(BotControlEvent_A_Event_1* control_event)작성후 OnActionEvent() 메소드 수정


 테스트 진행시 실행 순서
 1. 설정 파일 Test.json를 불러와 테스트할 action_list 를 불러옴
 2. 봇을 스레드마다 균등하게 분배해 생성
 3. 생성할 봇마다 action_list을 넣고 실행
