# Basic-Network-2024

리눅스 기반 네트워크 프로그래밍-2024 레포지토리

## 1일차(2024-06-11)

- 네트워크 프로그래밍, 소켓
  - 소켓
    - 물리적으로 연결된 네크워크 상에서의 데이터 송수신에 사용할 수 있는 소프트웨어적인 장치,
    - 소켓을 이용하여 데이터를 주고 받을 수 있음(네트워크 프로그래밍을 소켓 프로그래밍이라고 부르는 이유)

  - 소켓 구현
        **핵심(server 구현을 위해 4개의 함수를 호출해야함)**
    - 소 -> 소켓(socket) : 휴대폰 구입 | 소켓 생성
    - 말 -> 바인드 (bind) : 전화번호 할당 | IP주소와 PORT번호 할당
    - 리 -> 리슨 (listen) : 개통 | 연결요청 가능상태로 변경
    - 아 -> 엑셉트 (accept)  : 전화를 받음. ㅣ (연결 요청에 대한 수락)

      - socket()
        - 서버와 클라이언트가 통신을 하기 위해서는 소켓 라이브러리 사용, 소켓을 만들기 위해서 사용하는 함수
          - 함수 형태

                ```C

              #include <sys/socket.h>
                 int socket(int domain, int type, int protocol);
                ```

        - 반환 : 해당 소켓을 가리키는 소켓 디스크립터(socket descriptor,시스템이 특정 파일에 할당해준 정수값)를 반환, -1이 반환되면 생성 실패, 0 이상의 값이 나오면 socket descriptor 반환.
        - domain : 어떤 영역에서 통신할 것이니지에 대한 영역을 지정. 프로토콜 family를 지정해 주는 것 -> AF_UNIX(프로토콜 내부에서), AF_INEF(IPv4), AF_INET6(IPv6)
        - type : 어떤 타입의 프로토콜을 사용할 것인지 대해 설정. -> SOCK_STREAM(TCP), AF_DGRAM(UDP), SOCK_RAM(사용자 정의)
        - protocol : 어떤 프로토콜의 값을 결정하는 것 -> 대부분 0 그 외의 경우 IPPROTO_TCP, IPPROTO_UDP
      - bind()
        - 소켓에 주소를 할당하는 함수
        - 함수 형태

                ```C
                #include <sys/socket.h>
                int bind(int sockfd, struct sockaddr -addr, socklen_t addrlen);
                ```

        - 반환 : 성공시 0, 실패시 -1
        - 3가지 인자를 전달하여 소켓에 주소를 할당할 수 있다. 즉 socket()함수로 받아온 디스크립터 sockfd가 존재하는데, 이 디시크립터 파일에 해당하는 소켓에 serv_addr 주소를 할당하겠다는 의미
        - sockfd : socket()함수를 통해 배정받은 디스크립터 번호 serv_sock
        - -addr : IP주소와 PORT번호를 지정한 serv_addr 구조체
        - addrlen : 주소정보를 담은 변수의 길이
      - listen()
        - 연결요청을 대기하는 함수.  

                ```C
                #include <sys/socket.h>
                int listen(int sock, int backlog);
                ```

        - bind를 통해 하나의 소켓에 ip주소와 port 번호를 할당했으니, 이제 클라이언트가 해당 소켓에 연결할 수 있도록 요청을 대기하는 상태로 만들어줘야함. 즉, listen함수가 호출된 이후부터 클라이언트에서 connect를 호출할 수 있음.
        - 반환 : 성공시 0, 실패시 -1
        - sock : 소켓 디스크립터 번호
        - backlog : 연결요청을 대기하는 큐의 크기
          - 지정한 디스크립터의 소켓이 리스닝소이 되며, backlog만큼의 큐 공간을 가짐
      - accept()
        - 연결 요청을 수락하는 함수

                ```C
                #include <sys/socket.h>
                int accept(int sock, struct sockaddr-addr, socklen_t -addrlen);
                ```

        - 대기중인 클라이언트의 요청을 차례로 수락함으로써 데이터를 주고 받을 수 있게 됨.
        - 반환 : 성공시 새로운 디스크립트 번호, 실패시 -1
        - (주의. 앞서 이용하던 서버소켓(리스닝소켓)은 연결요청을 대기시키는 과정까지를 담당. accept()를 통해 새로 할당받은 소켓을 이용해 데이터 송수신을 할 수 있는 것)
        - sock : 서버소켓(리스닝 소켓)의 디스크립터 번호
        - addr : 대기 큐를 참조해 얻은 클라이언트의 주소 정보
        - addrlen : addr변수의 크기
        - -cf) clnt_sock에 새로운 소켓 디스크립터를 반환할 때에는 대기 큐에서 첫번째로 대기중인 연결요청을 참조한다. 이 때, 대기 큐가 비어있는 상황이라면 새로운 요청이 올 때까지 accept값은 반환되지 않고 대기(blocking)한다.-
      - connect()
        - client socket -> 전화를 거는 함수

                ```C
                #include <sys/socket.h>
                int connect(int sockfd, struct sockaddr -serv_addr, socklen_t addrlen)
                ```

        - 클라이언트에서 connect() 시스템 콜을 호출하면 listen()|accept()로 대기중이던 서버에 연결이 요청됨.서버는 accept() 함수를 정상 리턴함으로써 두 호스트간 연결이 성립됨.
        - sockfd : sockfd의 디스크립터 번호
        - -addr : 연결을 요청할 서버의 구조체 주소
        - addrlen : 서버 구조체 주소 변수의 길이

  - 리눅스 기반에서 실행하기
    - 실행하기 위해서는 서버를 먼저 실행해야 함
      - ./(실행파일명) 9190(포트번호)
    - 클라이언트 프로그램 실행
      - ./(실행파일명) 127.0.0.1(ip주소. 한대의 컴퓨터 내에서 서버와 클라이언트 프로그램을 실행시키는 경우 사용.) 9190(포트번호)

- 리눅스 기반 파일 조작
  - 리눅스에서의 소켓조작은 파일조작과 동일함. 파일 입출력 함수를 소켓 입축력(네트워크상에서의 데이터 송수신)에 사용할 수 있음.
    *cf)윈도우는 구분함*

  - 리눅스가 독립적으로 제공하는 파일 디스크립터
    - 별도의 생성과정을 거치지 않아도 프로그램이 실행되면 자동으로 할당됨.
    - 0 - 표준입력 : Standard Input
    - 1 - 표준출력 : Standard Output
    - 2 - 표준에러 : Standard Error

  - 파일 열기
  - 파일 닫기
  - 파일 데이터 쓰기
  - 파일에 저장된 데이터 읽기
  - fd_seri.c 예제

- 소켓의 프로토콜, 데이터 전송 특성
  - 프로토콜 - 컴퓨터 상호간의 대화에 필요한 통신규약(약속)
    - 프로토콜 체계(Protocol Family) - 프로토콜의 부류정보
      - PF_INET(IPv4 인터넷의 프로토콜 체계), PF_INET6(IPv6 인터넷의 프로토콜 체계) ...
    - 소켓의 타입(Type) - 소켓의 데이터 전송방식
      - 연결지향형 소켓 (SOCK_STREAM, TCP방식)
        - 중간에 데이터가 소멸되지 않고 목적지로 전송
        - 전송 순서대로 데이터가 수신됨
        - 전송되는 데이터의 경계(Boundary)가 존재하지 않는다. (read함수의 호출횟수와 write함수의 호출횟수는 연결지향형 소켓의 경우 큰 의미x)
        - 연결지향형 소켓은 자신과 연결된 상대 소켓의 상태를 파악해가며 데이터를 전송함. 데이터가 제대로 전송되지 않으면 데이터를 재전송. 소켓에 존재하는 버퍼가 다 차면 전송하지 않음
      - 비 연결지향형 소켓(SOCK_DGRAM, UDP방식)
        - 전송된 순서에 상관없이 가장 빠른 전송을 지향
        - 전송된 데이터는 손실의 우려가 있고, 파손의 우려가 있다.
        - 전송되는 데이터의 경계(Boundary)가 존재한다.

- 소켓에 할당되는 ip주소, port 번호
  - IP주소 (인터넷 주소)
    - IPv4 기준의 4바이트 IP주소는 네트워크 주소와 호스트(컴퓨터) 주소로 나뉨.
    - 주소의 형태에 따라서 A(0~127, 첫번째비트 0), B(128~191, 첫번째비트 10), C(192~223, 첫번째비트 110), D, E클래스로 분류됨. (E는 일반적이지 않은 예약된 주소 체계)
        ![IPv4 주소체계](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net001.png)

  - Port (포트번호)
    - 클라이언트 프로그램이 네트워크 상의 특정 서버 프로그램을 지정하는 방법으로 사용. 지금 실행되고 있는 프로그램
    - 포트번호는 중복으로 소켓에 할당할 수 없다.
    - 데이터 전송방식이 다를경우에는 port 번호가 같아도 상관없다.
    - 16비트 (2바이트, 0 ~ 65535)
    - 개인적으로 사용할때는 10000번 이상의 번호를 사용

- IPv4 기반의 주소표현을 위한 구조체
  - bind 함수에 주소정보를 전달하는 용도로 사용

    ```C
    struct sockaddr_in
    {
        sa_family_t sin_family // 주소 체계
        uint16_t sin_port // 16비트 TCP/UDP PORT 번호
        struct in_addr // 32비트 IP주소
        char sin_zero[8] // 사용되지 않음, 반드시 0으로 채워야함
    }
    ```

  - 위의 구조체는 IPv6을 사용하게 되었을때를 대비하여 만들어져있음. 그래서 사용되지 않는 sin_zero 같은 것이 존재함
  - 위의 구조체에서 사용된 또 다른 구조체 in_addr은 32bit IP주소정보를 담을 수 있도록 정의되어 있음.

    ```C
    struct in_addr
    {
        in_addr_t s_addr;   //32비트 IPv4 인터넷 주소
    } 
    ```

- 네트워크 바이트 순서와 인터넷 주소 변환
  - 바이트(Order) 순서와 네트워크 바이트 순서
    - 빅 엔디안 : 상위바이트의 값을 작은 번지수에 저장하는 방식
    - 리틀 엔디안 : 상위바이트의 값을 큰 번지수에 저장하는 방식
      - CPU의 데이터 저장방식을 의미하는 '호스트 바이트 순서(Host Byte Order)'는 CPU마다 다름
      - 문제해결을 위해 네트워크상으로 데이터를 전송할 때 데이터의 배열을 "빅 엔디안" 방식으로 통일(네트워크 바이트 순서)
      - 리틀 엔디안 시스템에서는 데이터를 전송하기 전에 빅 엔디안 정렬방식으로 재정렬 해야함.

        ![빅/리틀 에디안](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net002.png)

  - 바이트 순서의 변환(Endian Conversions)
    - unsigned short htons(usigned short); shott형 데이터를 호스트 바이트 순서에서 네트워크 바이트 순서로 변환
    - unsigned short ntohs(usigned short);
    - unsigned long htons(usigned long);
    - unsigned long ntohs(usigned long);
    - 변환하는 것 - h:host, n:network s:shoty l:long  to:to

## 2일차(2024-06-12)

- 문자열 정보 -> 네트워크 바이트 순서의 정수로 변환
  - in_addr_t inet_addr(const char - string);
  - int inet_aton(const char -string, struct in_addr- addr);

- IPv4 기반의 주소표현을 위한 구조체 (계속, 1일차에 같이 정리함.)

- scockaddr_in, in_addr 구조체에서 사용된 자료형
  - int9_t, uint8_t, int16_t, sa_family_t ...
  - 위와 같은 자료형은

- TCP/IP 프로토콜 스택
- 연결 요청을 허락하는 서버소켓, accept() 함수 호출에 의해 생성된, 실질적으로 데이터를 주고받은 클라이언트 소켓

- bind(), listen(), accept() 함수
- 공유기 관리자모드로 들어가기 (192.168.0.1) 접속 -> 포트포워드 설정에서  내부 ip주소(rpi ip주소), 외부포트 설정
- client ip주소 210.119.12.--(고정 ip주소) 서버 ip 입력, 포트 번호

