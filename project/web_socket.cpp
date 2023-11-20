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

int main(int argc, char ** argv){
    int serv_sock;
    struct sockaddr_in serv_addr;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);   //PF_INET: IPv4 | SOCK_STREAM: TCP 통신 | 0을 써주면 앞의 타입을 보고 자동으로 tcp면 tcp로, udp면 udp로 지정해줌.

    srv_addr.sin_family = AF_INET;  // 바인드할 때 씀. IPv4를 쓰겠다는 뜻
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