## 5일차(2024-06-17)
 
- send & recv 입출력 함수
    ```C
    #include <sys/socket.h>
    int send(int socket, const void *msg, size_t len, int flags);
    int recv(int socket, void *buf, size_t len, int flags);
    ```
    1) int socket: 통신의 주체가 되는 소켓 디스크립터
        - send - 정보를 받을 소켓 디스크립터 주소
        - recv - 정보를 보내는 소켓 디스크립터 주소

    2) const void *msg : 상대에게 보낼 자료의 포인터        
    
    3) void *buf : 받은 메세지를 저장할 버퍼 포인터
    
    4) size_t len : 전송되는 메세지의 크기 (byte 단위)

    5) int flags :  플레그(옵션)
        - MSG_OOB : 긴급 데이터의 전송을 위한 옵션            - MSG_PEEK : 입력버퍼에 수신된 데이터의 조재 유무 확인
        - MSG_DONTWAIT : 전송 전에 대기 상태가 필요하다면 기다리지 않고 -1반환하면서 복귀, 수신을 위해 대기가 필요하면 기다리지 않고 -1 반환하면서 복귀
        - MSG_NOSIGNAL : 상대방과 연결이 끊겼을 때, SIGPIPE 시그널을 받지 않도록 함.
    
    - 예제 실행 결과 확인
        - 긴급으로 메시지가 전달된 흔적이 보이지 않음. 
        - 소케은 더 빨리 전송하지 않고 Urgent-mode를 이용하여 긴급 상황의 발생을 알려 우리가 응급조치를 취하도록 도움
        - MSG_OOB 메시지라고 해서 더 빨리 전송되지 않음
        - 긴급으로 보낸 메시지의 양에 상관 없이 1바이트만 반환됨
    
    - 입력버퍼 검사
        - MSG_PEEK, MSG_DONTWAIT의 옵션지정으로 인해서 블로킹 되지 않고 데이터의 존재 유무를 확인
        - 버퍼에서 데이터를 읽으면 소멸된다. BUT MSG_PEEK 옵션을 지정하면 데이터를 읽어도 소멸되지 않음

- readv & writev 입출력 함수
    ```C
    #include <sys/uio.h>
    int writev(int fd, const struct iovec *vector, int count);
    int readv(int fd, const struct iovec *vector, int count);
    ```
    - 반환 : 성공시 전송한 바이트 수, 실패 시 -1
    - 인자 값
    1) fd - 데이터 전송의 목적지를 나타내는 소켓의 파일 디스크립터 전달, 반드시 소켓에만 해당하는 함수가 아니고 read, write함수처럼 파일이나 콘솔을 입,출력 대상으로 할 수 있음

    2) vector - 일반적으로 iovec 구조체 배열의 이름을 인자로 전달. iovec 구조체에는 전달하고자하는 데이터의 정보가 담겨짐.

    3) count - 데이터를 전송하기 위해 참고할 iovec 구조체 변수의 수를 지정.

    - writev 함수
        - 둘 이상의 영역에 나눠서 저장된 데이터를 묶어서 한번의 함수호출을 통해서 보낼 수 있음.
    - readv 함수
        - 단 한번의 함수호출을 통해 입력되는 데이터를 둘 이상의 영역에 나눠서 저장이 가능.
    - 사용, 장점
        - 여러 영역에 나뉘어 있는 데이터들을 하나의 배열에 순서대로 옮겨다 놓고 write 하뭇를 호출하는 것과 결과가 동일
        - 함수의 호출 횟수를 줄일 수 있음
        - 잘게 나뉜 데이터들을 출력버퍼에 한번에 밀어 넣기 때문에 하나의 패킷으로 구성되어서 전송될 확률이 높아지고, 전송속도의 향상도 기대할 수 있음

***
- 표준 입출력 함수
    - 장점
        1. 이식성이 좋음 (모든 컴파일러에서 지원함)
        2. 버퍼링을 통한 성능 향상에 도움이 됨

        ![표준입출력 함수 데이터 전송](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net11.png)
    
    - 예제 결과
        - (300Mbyte 파일을 대상으로 테스트 시) 표준 입출력 함수를 이용해 버퍼링 기반의 파일 복사를 진행할 때와 시스템 함수(버퍼링 없는 파일 복사)를 이용한 경우와 속도 차이가 매우 극명하게 나타남.
    
    - 불편사항
        1. 양방향 통신이 쉽지 않음
            - fopen 함수 호출 시 반환되는 File 구조체의 포인터를 대상으로 입출력을 진행하는 경우 데이터가 버퍼링 되기때문에 입출력을 동시에 진행되게 하는 것이 간단하지 않음
        2. 상황에 딸 fflush 함수의 호출이 빈번히 등장할 수 있음
        3. 파일 디스크립터를 FILE 구조체 포인터로 변환해야 함
            - 소켓 생성 시 반환되는 것은 파일 디스크립터, 표준 C 함수에서 요구하는 것은 FILE 구조체의 포인터이므로 변환해야함.

- 함수를 이용한 FILE 구조체 포인터로의 변환
    - fdopen 함수
        ```C
        #include <stdio.h>
        FILE * fdopen(int fildes, const char * mode);
        ```
        - 반환 : 성공 시 변환된 FILE 구조체 포인터, 실패 시 NULL
        - fildes - 변환할 파일 디스크립터를 인자로 전달
        - mode - 생성할 FILE 구조체 포인터의 모드(mode) 정보 전달
        - 예제 실습 
            - fdopen함수 호출 이후 표준입출력 함수 사용.
    
    - fileno 함수
        ```C
        #include <stdio.h>
        int fileno(FILE * stream);
        ```
        - 반환 : 성공 시 변환된 파일 디스크립터, 실패 시 NULL
        - 역으로 fileno 함수호출을 통해서 FILE 구조체 포인터를 파일 디스크립터로 변환
    
- 소켓 기반에서의 표준 C 입출력 함수의 호출 예시
    - 입력용, 출력용 FILE 구조체 포인터를 각각 생성해야함.
    - 표준 C 입출력 함수를 사용할 경우 소케의 버퍼 이외에 버퍼링이 되기 때문에 필요시 fflush 함수를 직접 호출해야 함
    - 순서
        1. 파일 디스크립터를 FILE 구조체 포인터로 변환
        2. 표준 입출력 함수의 호출
        3. 함수 호출 후 fflush 함수호출을 통해서 버퍼를 비워줌

    ```C
    readfp = fdopen(sock, "r");
    writefp = fdopen(sock, "w");
    while(1)
    {
        fputs("Input message(Q to quit) : ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q/n")|| !strcmp(message, "Q/n"))
            break;
        
        fputs(message, writefp);
        fflush(writefp);
        fgets(message, BUF_SIZE, readfp);
        printf("Message from server: %s", message);
    }
    ```
    - 예제 실습

***
- 입력 스트림과 출력 스트림의 분리
    - 앞의 스트림 분리는 멀티 프로세스 기반의 분리, 지금 분리는 FILE 구조체 기반의 분리 (P253, Ch10. 멀티프로세스 기반 서버 구현)
    - 이점
        - FILE 포인터는 읽기모드와 쓰기모드로 구분을 해야함
        - 읽기모드와 쓰기모드의 구분을 통한 구현 편의성 증대
        - 입력버퍼와 출력버퍼를 구분함으로 인한 버퍼링 기능 상향

    - 스트림 분리 이후 EOF에 대한 문제점
        - 하나의 소케을 대상으로 입력용, 출력용 FILE 구조체 포인터를 얻었더라도 이 중 하나의 대상을 fclose 함수를 호출하면 falf-close가 아닌 완전 종료가 진행된다.
            - 하나의 파일 디스크립터를 대상으로 FILE 포인터가 생성되었기 때문에 FILE 포인터가 종료되면 연결된 FILE 티스크립터도 종료됨.

    - 파일 디스크립터의 복사 후 스트림의 분리
        ```C
        #include <unistd.h>

        int dup(int fildes);
        int dups(int fildes, int fildes2);
        ```
        - 반환 - 성공 시 복사 된 파일 디스크립터, 실패 시 -1
        - fildes - 복사할 파일 디스크립터 전달
        - fildes2 - 명시적으로 저장할 파일 디스크립터의 정수 값 전달

        - dup 함수 호출을 통해서 복사된 파일 디스크립터를 대상으로 FILE 구조체 포인터를 생성
        -  파일 디스크립터로 변환해서 shutdown 함수를 호출하여 half-close가 진행되고, 이로 인해 상대방 영역으로 EOF가 전달됨.
        - EOF 전달을 목적으로하는 falf-close는 파일 디스크립터를 이용해서 진행해야함.

        - 예제 실습
            - fileno 함수호출 시 반환되는 파일 디스크립터를 대상으로 shutdown 함수를 포출하여 half-close가 진행되어 클라이언트로 EOF가 전달됨
            - shutdown 함수가 호출되면 복사 된 파일 디스크립터 수에 상관없이 half-close가 진행되며 이 과정에서 EOF또한 전달됨.


        ![스트림 분리](https://raw.githubusercontent.com/Juhyi/Bascic-Network-Programming-2024/main/imges/net12.png)
        


