#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono> // 추가

using boost::asio::ip::udp;

std::vector<char> protocol_packet(){
    static std::vector<char> data = {0x00, 0x03, 0x00, 0x0c, 0x14, 0x00};
    data[5] = (data[5] + 1) % 256; // 6번째 byte 1 더하기

    return data;
}

int main() {
    try{
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::v4());

        udp::endpoint server_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888);
        int count = 0;

        while(count++ < 2560) {
            std::vector<char> data = protocol_packet();
            boost::system::error_code error;
            size_t send_bytes = socket.send_to(boost::asio::buffer(data), server_endpoint, 0, error);

            if(send_bytes == 0) {
                std::cerr << "send 실패: " << error << std::endl;
                return 0;
            }

            // 서버가 처리할 시간을 주기 위해 잠시 대기
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

    } catch(std::exception& e) { // 예외 객체에 대한 참조로 수정
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
