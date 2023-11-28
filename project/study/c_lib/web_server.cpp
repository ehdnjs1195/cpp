#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

int g_clnt_socks[CLNT_MAX]; // 클라이언트 소켓
int g_clnt_count = 0;

int main(int argc, char ** argv){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in clnt_addr;
    int clnt_addr_size;
    
    struct sockaddr_in serv_addr;
    // 1. server socket 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);   //PF_INET: IPv4 | SOCK_STREAM: TCP 통신 | 0을 써주면 앞의 타입을 보고 자동으로 tcp면 tcp로, udp면 udp로 지정해줌.

    serv_addr.sin_family = AF_INET;  // 바인드할 때 씀. IPv4를 쓰겠다는 뜻
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    // TAS IP주소
    // serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8888);   // port번호

    // 2. IP주소, Port번호와 바인드.
    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {  // bind(). -1 반환은 bind 실패.
        printf("bind error\n"); 
    }

    // 3. 요청 대기.
    if(listen(serv_sock, 5) == -1) {    // 5는 백로그 큐 크기. listen 대기 큐
        printf("listen error");
    }

    char buff[200]; // 데이터 버퍼
    int recv_len = 0;
    while(1) {
        clnt_addr_size = sizeof(clnt_addr);
        // 4. 연결 수립. (통신 소켓 생성)
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, (socklen_t *)&clnt_addr_size);
        g_clnt_socks[g_clnt_count++] = clnt_sock;   

        // 5. 데이터 송수신 처리
        char msg[256] = "";	// 송수신에 사용할 메시지 버퍼
        while (recv(clnt_sock, msg, sizeof(msg),0) > 0) {	//메시지를 수신할 때 recv 함수를 사용함. 반환값은 수신한 메시지 길이. 상대가 끊으면 0을 반환함.
            printf("recv:%s\n", msg);
            // send(clnt_sock, msg, sizeof(msg), 0);	// 받은 메시지를 다시 보내는 에코 작용
        }
        close(clnt_sock);
    }
    // 6. 연결 해제
    close(serv_sock);
}



/*
    socket(매개변수1, 매개변수2, 매개변수3);
    
    #매개변수1
    af: 네트워크 주소 체계
        #define AF_INET     2   //IPv4
        #define AF_INET6    23  //IPv6

    #매개변수2
    type: 소켓 타입
        #define SOCK_STREAM     1   // 스트림, TCP 프로토콜의 전송 방식
        #define SOCK_DGRAM      2   // 데이터 그램, UDP 프로토콜의 전송 방식
        #define SOCK_RAW        3   // RAW 소켓, 가공하지 않은 소켓
    
    #매개변수3
    protocal: 프로토콜
        #define IPPROTO_TCP     6   // TCP 프로토콜
        #define IPPROTO_UDP     17  // UDP 프로토콜
        #define IPPROTO_RAW     255 // RAW 
    
    프로토콜 정의 
        IPPROTO_TCP : TCP 프로토콜을 사용함
        IPPROTO_UDP : UDP 프로토콜을 사용함
        IPPROTO_HOPOPTS
            - 첫번째, 두번째 매개변수를 기준으로 자동지정
            - 세번째 매개변수에 0을 넣어주면 자동으로 첫번째, 두번째 매개변수를 기준으로
              인자값을 지정해준다.(IPPROTO_HOPOPTS와 같은 역할).
*/