#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <stdio.h>
#include <future>   // async, promise, future
// #include <mutex>
#define PORT_NUM 8888
using boost::asio::ip::udp;

void data_handler(udp::socket&);
void data_processing(char&, size_t&, udp::endpoint&);

void data_processing(char& data, size_t& bytes_received, udp::endpoint& client_endpoint){ // 받은 데이터 로깅핸들
    std::vector<int> packet(data, data + bytes_received); // 받은 데이터(packet)

    std::cout << "Received from [" << client_endpoint.address() << "|" << client_endpoint.port() << "]: " ;
    for (int value : packet) {
        printf("%02X ", value);
    }
    std::cout << " | 작업한 쓰레드: " << std::this_thread::get_id() <<std::endl;
}

void data_handler(udp::socket& socket){ // 클라이언트 처리 핸들
    char data[1024];                    // 교통신호 데이터
    udp::endpoint client_endpoint;
    while(true){
        size_t bytes_received = socket.receive_from(boost::asio::buffer(data), client_endpoint);
        auto f = std::async([&]() {
            std::cout << "data: " << data << std::endl;
            data_processing(*data, bytes_received, client_endpoint); });

        std::chrono::milliseconds(500); // 0.5s
    }

}



int main() {
    try{
        boost::asio::io_service io_service;
        std::cout << "Server start" << std::endl;
        
        udp::socket socket(io_service, udp::endpoint(udp::v4(), PORT_NUM));
        // todo: socket 생성 실패 처리

        std::thread work_thread(data_handler, std::ref(socket));
        // todo: client 데이터 수신 실패처리
        
        work_thread.join(); // thread join

    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}