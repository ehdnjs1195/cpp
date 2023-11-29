#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <stdio.h>
#define PORT_NUM 8888
#define THREAD_SLEEP_TIME_MS 10
using boost::asio::ip::udp;


void interval(udp::socket& socket,udp::endpoint& client_endpoint , const std::chrono::milliseconds& duration){
    while(true) {
        std::this_thread::sleep_for(duration);

        unsigned char data[1024];   // char 는 최상위 비트가 1이면 부호가 바뀐다. 따라서 unsigned char 타입이어야 함.
        size_t bytes_received = socket.receive_from(boost::asio::buffer(data), client_endpoint);
        std::vector<int> receive_data(data, data+bytes_received);

        std::cout << "Received from [" << client_endpoint.address() << "|" << client_endpoint.port() << "]: " ;
        for (int value : receive_data) {
            printf("%02X ", value);
        }
        std::cout << std::endl;
        
    }
}
int main() {
    try{
        std::cout << "Server start" << std::endl;
        boost::asio::io_service io_service; 
        
        udp::socket socket(io_service, udp::endpoint(udp::v4(), PORT_NUM)); //socket 생성
        
        while(true) {
            char data[1024];
            udp::endpoint client_endpoint;
            // receive_from 함수를 사용하여 클라이언트의 연결 대기.
            size_t bytes_received = socket.receive_from(boost::asio::buffer(data), client_endpoint);
            // 작업스레드: interval 형태로 소켓과 지연시간 전달
            std::thread works = std::thread(interval, std::ref(socket), std::ref(client_endpoint), std::chrono::milliseconds(THREAD_SLEEP_TIME_MS));
            works.join();
        }
        
        
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}

