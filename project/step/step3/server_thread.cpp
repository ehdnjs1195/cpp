#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
// #include <mutex>
#define PORT_NUM 8889
#define THREAD_SLEEP_TIME_MS 100

using boost::asio::ip::udp;


void packet_handler(std::vector<int>& packet, udp::endpoint& client_endpoint){ // 받은 데이터 로깅핸들
    std::cout << "Received from [" << client_endpoint.address() << "|" << client_endpoint.port() << "]: " ;
    for (int value : packet) {
        printf("%02X ", value);
    }
    std::cout << " | [thread]: " << std::this_thread::get_id() << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME_MS));
}

void session(udp::socket& socket){   // 클라이언트 처리 핸들
    udp::endpoint client_endpoint;          
    boost::system::error_code error;
    while(true){
        // std::vector<unsigned char> buffer;  // packet buffer
        unsigned char buffer[1024];
        size_t bytes_received = socket.receive_from(boost::asio::buffer(buffer), client_endpoint, 0 ,error);
        if(error){
            std::cerr << "[UDPServer] receive from error: " << error.message() << std::endl;
            continue;
        }
        std::vector<int> packet(buffer, buffer + bytes_received);
        // thread
        std::thread(packet_handler, std::ref(packet), std::ref(client_endpoint)).join();
    }
}

int main() {
    try{
        boost::asio::io_service io_service;
        std::cout << "Server start" << std::endl;
        
        udp::socket socket(io_service, udp::endpoint(udp::v4(), PORT_NUM));
        // socket 생성 실패 처리

        std::thread work_thread(session, std::ref(socket));
        // client 데이터 수신 실패처리

        work_thread.join(); // thread join

    } catch(std::exception e) {
        std::cerr << "Exception occured! :" <<e.what() << std::endl;
    }
}