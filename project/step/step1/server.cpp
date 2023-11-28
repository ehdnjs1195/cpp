#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <string>
#define PORT_NUM 8888
#define THREAD_SLEEP_TIME_MS 100
using boost::asio::ip::udp;


void interval(udp::socket& socket,udp::endpoint& client_endpoint , const std::chrono::milliseconds& duration) {
    while(true) {
        std::this_thread::sleep_for(duration);

        char data[1024];
        size_t bytes_received = socket.receive_from(boost::asio::buffer(data), client_endpoint);

        std::cout << "Received from " << client_endpoint.address() << ": " << client_endpoint.port() << ": " << data << std::endl;
    }
}

int main() {
    try{
        boost::asio::io_service io_service; //io_context와 같음
        // socket을 생성하면서 endpoint 전달. => 명시적인 bind 호출이 필요없음. 간결함.
        udp::socket socket(io_service, udp::endpoint(udp::v4(), PORT_NUM)); 
        /*
                아래와 같이 일일이 상세하게 bind할 필요가 없음.
            boost::asio::ip::udp::socket socket(io_service, boost::asio::ip::udp::v4());
            udp::endpoint listen_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), PORT_NUM);
            socket.bind(listen_endpoint);
        */
    
        // locking
        // std::mutex mtx;
        // std::lock_guard lock(mtx); // 작업 종료되면 자동해제
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

