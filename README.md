# IoT-Network-programming-2024
IoT 네트워크 프로그래밍-2024 레포지토리

## 1일차
- IP   
    - ip 주소 : (cmd -> ipconfig로 확인 가능)
        - **ipv4 (4바이트)** /ipv6
    - 기본 게이트웨이 : 내 컴퓨터로 들어오는 출입문 개념, 
    - 서브넷 마스크

- TCP 
    - tcp : 전송하는 방식 중 한가지 (일반적임), 정확하게 데이터를 주고 받아야될때는 tcp (데이터 손실이 없어야 함) ex. 압축파일 전송
    - udt : 데이터를 1,2개 잃어버려도 괜찮음 ex. 영화 전송

- usb -> 블루투스 직렬 통신

**핵심**
- 소 -> 소켓(socket) : 휴대폰 구입 | 소켓 생성
- 말 -> 바인드 (bind) : 전화번호 할당 | IP주소와 PORT번호 할당
- 리 -> 리슨 (listen) : 개통 | 연결요청 가능상태로 변경
- 아 -> 엑셉트 (accept)  : 전화를 받음. ㅣ (연결 요청에 대한 수락)
    => server 구현을 위해 4개의 함수를 호출해야함

- socket() 함수 : 서버와 클라이언트가 통신을 하기 위해서는 소켓 라이브러리 사용, 소켓을 만들기 위해서 사용하는 함수
	- 헤더파일 : <sys/types.h>, <sys/socket.h>
	- 함수 형태 : int socket(int domain, int type, int protocol);
- bind() 함수 : 
- listen()
- accept()

- client socket -> 전화를 거는 기능을 하는 함수 : connect()

- 웹 서버에서 정보를 보내주고 웹브라우저가 해석하여 화면을 보여줌

- 프로토콜 
    - 소켓 타입 : 연결지향형 소켓 (TCP), 비 연결지향형 소켓(UDP)
