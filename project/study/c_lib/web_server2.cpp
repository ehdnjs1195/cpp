#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
// #include <malloc.h>

#define IP_ADDR "127.0.0.1" //IP주소10.20.0.47
#define PORT_NUM 8888	    //포트번호
#define BLOG_SIZE 5		    //백로그 큐 사이즈
#define MAX_MSG_LEN 256	    //주고 받는 메시지 버퍼 크기도 매크로 상수로 정의함.

//대기 소켓을 생성하여 가동하는 부분을 함수로 만들기
int SetTCPServer(short pnum, int blog);	//인자로 포트번호와 백로그 큐 크기를 전달함.
void AcceptLoop(int sock);	// 함수로 정의
// IN_ADDR GetDefaultMyIP();

int main() {
	int sock = SetTCPServer(PORT_NUM, BLOG_SIZE); //대기 소켓 가동
	AcceptLoop(sock);//Accept Loop
	close(sock);//소켓 해제

	return 0;
}

//TCP 서버 기본 절차: sockt - bind - listen(- Accept Loop)
int SetTCPServer(short pnum, int blog) {
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// 대기소켓 생성, IPv4에 해당하는 AF_INET 전달, IPv6는 AF_INET6 임.
	struct sockaddr_in servaddr = { 0, };	//서버 주소
	servaddr.sin_family = AF_INET;
	// servaddr.sin_addr = GetDefaultMyIP();
	servaddr.sin_addr.s_addr = inet_addr(IP_ADDR);  
	servaddr.sin_port = htons(pnum);// 네트워크에서 사용하기 때문에 호스트 바이트오더를 네트워크로 변환한다. 포트번호는 2바이트이다.(s)

	//네트워크 인터페이스와 소켓 결합. bind할 자신의 IP와 PORT번호를 소켓 주소에 설정한다.
	int re = 0;
	re = bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (re == -1) {	//바인드 실패 -1 리턴됨. (-1 => 0xFFFFFFFF => SOCKET_ERROR를 반환)
        printf("bind error\n");
		return -1;
	}

	// 백로그 큐 크기 설정
	re = listen(sock, blog);
	if (re == -1) { // -1 => 0xFFFFFFFF => SOCKET_ERROR를 반환
        printf("listen error\n");
        return -1; 
    }	

	// 서버가 시작할 때 자신의 IP:PORT를 출력하게 하기
	printf("%s:%d Setup\n", inet_ntoa(servaddr.sin_addr), pnum);
	return sock;
}
void DoIt(int dosock);
void AcceptLoop(int sock) {	// 대기 소켓을 입력 인자로 설정.
	int dosock;	// 연결한 클라이언트와 통신할 소켓 변수를 선언.
	struct sockaddr_in cliaddr = { 0, };
	int len = sizeof(cliaddr);
	while (true) {
		dosock = accept(sock, (struct sockaddr *)&cliaddr, (socklen_t *)&len);	//연결수락
		if (dosock == -1) {
			perror("accept 실패");	// perror는 에러 메시지와 전달한 메시지를 출력하는 함수
			break;
		}
		printf("%s:%d의 연결 요청 수락\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		DoIt(dosock);	//클라이언트와 송수신 하는 부분
	}
}

void DoIt(int dosock) {
	char msg[MAX_MSG_LEN] = "";	// 송수신에 사용할 메시지 버퍼
	// ## recv, send의 4번째 인자는 옵션임.(여기선 다루지 않는다.)
	while (recv(dosock, msg, sizeof(msg),0) > 0) {	//메시지를 수신할 때 recv 함수를 사용함. 반환값은 수신한 메시지 길이. 상대가 끊으면 0을 반환함.
		printf("recv:%s\n", msg);
		// send(dosock, msg, sizeof(msg), 0);	// 받은 메시지를 다시 보내는 에코 작용
	}
	close(dosock);	//서버소켓 닫기
}


// IN_ADDR GetDefaultMyIP() {
// 	char localhostname[MAX_PATH];
// 	IN_ADDR addr = { 0, };
// 	if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR) {	
// 		return addr;	
// 	}
// 	HOSTENT* ptr = gethostbyname(localhostname);	
// 	while (ptr && ptr->h_name) {	
// 		if (ptr->h_addrtype == PF_INET) {	
// 			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);	
// 			break;
// 		}
// 		ptr++;
// 	}
// 	return addr;
// }