#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <stdio.h>
#define PORT_NUM 8888
#define THREAD_SLEEP_TIME_MS 100
using boost::asio::ip::udp;


void interval(udp::socket& socket,udp::endpoint& client_endpoint , const std::chrono::milliseconds& duration) {
    while(true) {
        std::this_thread::sleep_for(duration);

        char data[1024];
        size_t bytes_received = socket.receive_from(boost::asio::buffer(data), client_endpoint);
        std::string print_data = "";
        for(int i=0; i<bytes_received; i++) {
            if(i!=0 && i%2==0) print_data += " ";
            print_data += data[i];
        }
        std::cout << "Received from [" << client_endpoint.address() << "|" << client_endpoint.port() << "]: " << print_data << std::endl;
    }
}
void interval2(udp::socket& socket,udp::endpoint& client_endpoint , const std::chrono::milliseconds& duration){
    while(true) {
        std::this_thread::sleep_for(duration);

        char data[1024];
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
            std::cout << bytes_received << std::endl;
            // 작업스레드: interval 형태로 소켓과 지연시간 전달
            std::thread works = std::thread(interval2, std::ref(socket), std::ref(client_endpoint), std::chrono::milliseconds(THREAD_SLEEP_TIME_MS));
            works.join();
        }
        
        
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}

