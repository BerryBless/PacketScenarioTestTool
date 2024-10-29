# PacketScenarioTestTool

Bot이 각 Action을 가지고 있고, 이 Action의 조합으로 서버를 테스트 하는 툴입니다.

![image](https://github.com/user-attachments/assets/8aa4b182-e6dc-46fd-980e-0c92fad9968f)

테스트 하고 싶은 시나리오를 BotControlAction을 상속 받아 TestAction을 만들고
BotController에 등록하여 해당 Action을 실행하도록 설계했습니다.
