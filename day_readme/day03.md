## 3일차 (2024-06-13)
* 157~ 227
* reseadr_eserver.c 실행파일 - ch.4 echo_client.c의 실행파일 eclient와 같이 실행하여 결과 확인하기 
    - client에서 먼저 연결 종료를 요청하는 경우에는 문제 발생 X 
    - But Server에서 먼저 연결 종료시 같은 포트번호로 재실행시 bind() error가 발생함. 
     
- Clinet가 먼저 연결 종료를 요청한 경우에는 왜 오류가 안생길까 ??
 - server가 client를 찾아가는 경우에 당연하게 ip + port 번호가 필요.
 - client가 사용하는 포트 번호는 서버에서 랜덤으로 부여하기 때문에 문제가 발생하지 않음
 - 서버에서 연결을 끊었을 경우에는 서버의 포트가 time- way에 걸리기 때문에 약 3분간 연결이 되지 않는다.

 * Nagle 알고리즘
    - 앞에 전송한 ack 메세지를 받아야 다음 데이터를 전송하는 알고리즘
    - 단점 : 용량이 큰 파일 데이터의 전송의 경우에는 Nagle의 적용 여부에 따른 트래픽 차이가 크지않으면서도 적용하는 것보다 데이터 전송이 빠름.

* 멀티프로세스 기반의 서버 구현 (이전까지는 기본적인 설명이였고 이제 진짜 서버같은거 배우는거!)
    - 프로세스 : 메모리 공간을 차지한 상태에서 실행중인 프로그램


    - 프로세스 생성
        - fork() 
        ```C
        #include <unistd.h>
        pid_t fork(void);
        ```
        - 반환 : 성공 시 프로세스 ID, 실패 시 -1 
    
    - fork함수는 복사본을 생성 -> 새로운 프로세스가 아닌 이미 실행중인 fork함수를 호출한 프로세스를 복사 
        - 부모 프로세스 - fork 함수를 호출한 프로세스, fork함수의 반환 값은 자식 프로세스의 ID (pid : 운영체제에서 프로세스를 구분하기 위해 부여하는 번호)
        - 자식 프로세스 : fork 함수의 호출에 의해 생성된 프로세스, fork함수의 반환 값은 0 
    - fork 함수의 반환 이후에 프로세스가 각각 독립적으로 실행됨.

* 좀비 프로세스
    - 실행이 완료된 후에도 소멸되지 않은 프로세스
    - 프로세스도 main함수가 반환되면 소멸되어야 함.
    - 소멸되지 않았다 == 사용한 리소스가 메모리 공간에 존재
    - 생성 원인
        - 자식 프로세스가 종료되면서 반환하는 상태 값이 부모 프로세스에게 전달되지 않을 경우!
        1. 인자를 전달하면서 exit를 호출하는 경우
        2. main 함수에서 return문을 실행하면서 값을 반환하는 경우
        - -> 자식 프로세스의 종료 상태 값이 운영체젱 전달되는 경로
    
    - 좀비 프로세스 생성 확인
        - 현재 실행중인 프로세스 확인 - cmd에서 ps au 입력
        - 자식 프로세스의 종료 값을 반환 받을 부모 프로세스가 소멸되기 전에 좀비의 생성 확인해야함.
            - 부모 프로세스가 종료되면 좀비 상태였던 자식 프로세스도 함께 소멸하기 때문.


        ![좀비프로세스 생성 전](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net003.png)

        ![좀비프로세스 생성 확인](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net004.png)