# Basic-Network-2024
리눅스 기반 네트워크 프로그래밍-2024 레포지토리

## 1일차(2024-06-11) [🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day01.md)
* 네트워크 프로그래밍, 소켓
    - 소켓 
    - 소켓 구현
        + socket(), bind(), listen(), accept(), connect()
    - 리눅스 기반에서 실행하기
    * 리눅스 기반 파일 조작
        - 리눅스가 독립적으로 제공하는 파일 디스크립터 - 0, 1, 2
        - 파일 열기 -open()
        - 파일 닫기 - close()
        - 파일 데이터 쓰기 - write()
        - 파일에 저장된 데이터 읽기 - read()
    - fd_seri.c 예제 
* 소켓의 프로토콜, 데이터 전송 특성
    - 프로토콜 - 컴퓨터 상호간의 대화에 필요한 통신규약(약속)
        + 프로토콜 체계(Protocol Family) - 프로토콜의 부류정보
        + 소켓의 타입(Type) - 소켓의 데이터 전송방식
            + 연결지향형 소켓 (SOCK_STREAM, TCP방식)
            + 비 연결지향형 소켓(SOCK_DGRAM, UDP방식)
* 소켓에 할당되는 ip주소, port 번호
    - IP주소 (인터넷 주소)
    - Port (포트번호)
* IPv4 기반의 주소표현을 위한 구조체
* 네트워크 바이트 순서와 인터넷 주소 변환
    - 바이트 순서의 변환(Endian Conversions)


## 2일차(2024-06-12) [🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day02.md)
* 네트워크 바이트 순서와 인터넷 주소 변환
    - 문자열 정보 -> 정수 변환
        + inet_addr(), inet_aton(), inet_ntoa()
    - 인터넷 주소의 초기화
        + 소켓생성과정에서 흔히 보이는 인터넷 정보의 초기화 방법
            + memset 함수 
            + atoi 함수
    - 클라이언트의 주소정보 초기화
        + INADDR_ANY
     - 소켓에 인터넷 주소 할당
        + 초기화된 주소정보 소켓에 할당 -> bind()  
 
* TCP/ UDP
    - TCP/ip 프로토콜 스택
    - Link & IP 계층
    - TCP/UDP 계층
    - APPLICATION 계층
* TCP 기반 서버/클라이언트
    - TCP기반 서버 구현
        - TCP 서버의 기본적이 함수호출 순서
            + socket() -> bind() -> listen() -> accept() -> read()/write() <데이터 송수신> -> close() 
        - 연결요청 대기 상태로 진입
        - 클라이언트의 연결 요청 수락
    - TCP기반 클라이언트 구현
        - TCP 클라이언트의 기본적인 함수호출 순서  
            + socket() -> connect() -> read()/write() -> close()
        - 클라이언트의 연결 요청
* Iterative 기반의 서버, 클라이언트 구현
* 에코 클라이언트 구현
* TCP 이론
* UDP
* UDP 기반 서버/클라이언트 구현
* 서버- 클라이언트 실습
 
## 3일차 (2024-06-13) [🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day03.md)
* 157~ 227
* reseadr_eserver.c 실행파일 - ch.4 echo_client.c의 실행파일 eclient와 같이 실행하여 결과 확인하기 
- Clinet가 먼저 연결 종료를 요청한 경우에는 왜 오류가 안생길까 ??
* Nagle 알고리즘
* 멀티프로세스 기반의 서버 구현 (이전까지는 기본적인 설명이였고 이제 진짜 서버같은거 배우는거!)
    - 프로세스 : 메모리 공간을 차지한 상태에서 실행중인 프로그램
    - 프로세스 생성
        - fork()
* 좀비 프로세스
    - 좀비 프로세스 생성 확인
        ![좀비프로세스 생성 확인](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net004.png)

## 4일차 (2024-06-14) ![🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day04.md)
- 좀비 프로세스 소멸
    - 1. wait() 함수 사용 
    - 2. waitpid() 함수 사용

- 시그널 핸들링 
    - 시그널 등록 함수 
        - alarm () 함수
    - sigaction ()
- 시그널 핸들리을 통한 좀비 프로세스 소멸
    - 예제 실습
    
    ![좀비 프로세스 소멸](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net008.png)

- 멀티태스킹 기반 다중 접속

- 다중접속 서버의 구현
    - [프로세스 기반의 다중접속 서버모델]
    - 예제 실습
    [서버 실행화면] 


         ![서버 실행화면](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net006.png)


     [클라이언트 실행화면] 


         ![클라이언트 실행화면](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net007.png)

- fork 함수호출을 통한 파일 디스크립터의 복사
    ![복사된 파일 디스크립터 정리](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net9.png)

- TCP의 입출력 루틴(Routine) 분할
    - 이점
        - 입출력 루틴을 분할하면 보내고 받는 구조가 아니라 둘을 동시에 진행할 수 있음.

- 프로세스간 통신
    - 두 프로세스 사이에서의 데이터 전달
- 프로세스간 통신의 어려움
    - 모든 프로세스는 자신만의 메모리 공간을 독립적으로 구성함.
- 파이프(PIPE) 기반의 프로세스간 통신
    - 파이프 생성 함수 -pipe()
    - pipe1.c 예제 (단방향 통신)

        ![pipe 통신경로](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net10.png)

        - 자식은 입력 경로에만 부모는 출력 경로에만 접근해서 통신을 했음.
    
    - 파이프 기반의 프로세스간 양방향 통신    
    - 메시지를 저장하는 에코 서버 예제 실습

- IO 멀티플렉싱(Multiplexing)
   - select 함수
    - 기능
    - 호출방법과 순서
        1. [파일 디스크립터의 설정][검사의 범위 지정][타임아웃의 설정] - 관찰의 대상을 묶고, 관찰의 유형을 지정
        2. [select함수 호출] - 관찰 대상의 변화를 물음.
        3. [호출 결과 확인] - 물음에 대한 답을 듣는다.
        - 파일 디스크립터의 설정
        - 검사 범위 지정
            - 타임아웃 설정
    - select 함수

- 멀티플렉싱 서버의 구현 
    - 예제 실습

## 5일차(2024-06-17) ![🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day05.md)
- send & recv 입출력 함수
    - 예제 실행 결과 확인
        - 긴급으로 메시지가 전달된 흔적이 보이지 않음. 
        - 소케은 더 빨리 전송하지 않고 Urgent-mode를 이용하여 긴급 상황의 발생을 알려 우리가 응급조치를 취하도록 도움
        - MSG_OOB 메시지라고 해서 더 빨리 전송되지 않음
        - 긴급으로 보낸 메시지의 양에 상관 없이 1바이트만 반환됨
    
    - 입력버퍼 검사
        - MSG_PEEK, MSG_DONTWAIT의 옵션지정으로 인해서 블로킹 되지 않고 데이터의 존재 유무를 확인
        - 버퍼에서 데이터를 읽으면 소멸된다. BUT MSG_PEEK 옵션을 지정하면 데이터를 읽어도 소멸되지 않음

- readv & writev 입출력 함수
    - writev 함수
    - readv 함수
    - 사용, 장점
        - 여러 영역에 나뉘어 있는 데이터들을 하나의 배열에 순서대로 옮겨다 놓고 write 하뭇를 호출하는 것과 결과가 동일
        - 함수의 호출 횟수를 줄일 수 있음
        - 잘게 나뉜 데이터들을 출력버퍼에 한번에 밀어 넣기 때문에 하나의 패킷으로 구성되어서 전송될 확률이 높아지고, 전송속도의 향상도 기대할 수 있음

- 표준 입출력 함수
    - 장점
        1. 이식성이 좋음 (모든 컴파일러에서 지원함)
        2. 버퍼링을 통한 성능 향상에 도움이 됨

        ![표준입출력 함수 데이터 전송](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net11.png)
    
    - 예제 결과
        - (300Mbyte 파일을 대상으로 테스트 시) 표준 입출력 함수를 이용해 버퍼링 기반의 파일 복사를 진행할 때와 시스템 함수(버퍼링 없는 파일 복사)를 이용한 경우와 속도 차이가 매우 극명하게 나타남.
    
    - 불편사항
        1. 양방향 통신이 쉽지 않음
        2. 상황에 딸 fflush 함수의 호출이 빈번히 등장할 수 있음
        3. 파일 디스크립터를 FILE 구조체 포인터로 변환해야 함

- 함수를 이용한 FILE 구조체 포인터로의 변환
    - fdopen 함수
    - fileno 함수
- 소켓 기반에서의 표준 C 입출력 함수의 호출 예시
    - 입력용, 출력용 FILE 구조체 포인터를 각각 생성해야함.
    - 표준 C 입출력 함수를 사용할 경우 소케의 버퍼 이외에 버퍼링이 되기 때문에 필요시 fflush 함수를 직접 호출해야 함
    - 순서
        1. 파일 디스크립터를 FILE 구조체 포인터로 변환
        2. 표준 입출력 함수의 호출
        3. 함수 호출 후 fflush 함수호출을 통해서 버퍼를 비워줌
    - 예제 실습

- 입력 스트림과 출력 스트림의 분리
    - 앞의 스트림 분리는 멀티 프로세스 기반의 분리, 지금 분리는 FILE 구조체 기반의 분리 (P253, Ch10. 멀티프로세스 기반 서버 구현)
    - 이점
        - FILE 포인터는 읽기모드와 쓰기모드로 구분을 해야함
        - 읽기모드와 쓰기모드의 구분을 통한 구현 편의성 증대
        - 입력버퍼와 출력버퍼를 구분함으로 인한 버퍼링 기능 상향

    - 스트림 분리 이후 EOF에 대한 문제점
        - 하나의 소케을 대상으로 입력용, 출력용 FILE 구조체 포인터를 얻었더라도 이 중 하나의 대상을 fclose 함수를 호출하면 falf-close가 아닌 완전 종료가 진행된다.

    - 파일 디스크립터의 복사 후 스트림의 분리
        - 예제 실습
            - fileno 함수호출 시 반환되는 파일 디스크립터를 대상으로 shutdown 함수를 포출하여 half-close가 진행되어 클라이언트로 EOF가 전달됨
            - shutdown 함수가 호출되면 복사 된 파일 디스크립터 수에 상관없이 half-close가 진행되며 이 과정에서 EOF또한 전달됨.


        ![스트림 분리](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net12.png)
        

## 6일차 ![🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day06.md)
- epoll의 이해
    - select 기반 IO 멀티플렉싱이 느린 이유
        1. select 함수 호출 이후에 항상 등장하는, 모든 디스크립터를 대상으로 하는 반복문
        2. 호출할 때마다 인자로 매번 전달해야 하는 관찰대상에 대한 정보들
    - 해결책
        - 운영체제 레벨에서 멀티플렉싱 기능을 지원해야한다는 의미.
        - 리눅스에서는 epoll, 윈도우에서는 IOCP가 그 예시이다.

    - 단점에도 사용할만한 이유
        - 서버의 접속사 수가 많지 않고 다양한 운영체제에서 운영이 가능해야 한다면 사용에 용이
        
    - epoll의 장점
        1. 상태변화의 확인을 위한, 전체 파일 디스크립터를 대상으로 하는 반복문이 필요 X
        2. select 함수에 대응하는 epoll_wait 함수호출 시, 관찰대상의 정보를 매번 전달할 필요가 X
    
- epoll의 활용
    - 구현에 필요한 함수 (3개의 함수 호출을 통해 epoll기능이 완성)
        1. epoll_create - epoll 파일 디스크립터 저장소 생성
        2. epoll_ctl - 저장소에 파일 디스크립터 등록 및 삭제
        3. epoll_wait - select 함수와 마찬가지로 파일 디스크립터의 변화를 대기
    - 소켓 디스크립터의 등록 및 이벤트 발생의 확인에 사용되는 구조체

    - epoll_creat() 함수

## 7일차 ![🔗자세한 내용 보기](https://github.com/Juhyi/Bascic-Network-Programming-2024/blob/main/day_readme/day07.md)
- 개인평가
    - 라즈베리파이로 웹페이지 서버 구현하기
        - putty에서 ./실행파일명 포트번호 입력후
        - web에서 고정ip 입력:포트번호로 접속

        ![실행결과](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net13.png)