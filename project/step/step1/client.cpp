#include <iostream>
#include <boost/asio.hpp>
#include <iomanip>
#include <sstream>
#include <vector>
using boost::asio::ip::udp;

std::vector<char> protocol_data(){
    static std::vector<char> data = {0x00, 0x03, 0x00, 0x0c, 0x14, 0x00};
    // std::vector<char> buffer(data.begin(), data.end());  // byte 데이터로 변형
    data[5] = (data[5] + 1) % 256; // 6번째 byte 1 더하기

    return data;
}
int main() {
    try{
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::v4());

        udp::endpoint server_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888);
        int count =0;
        while(count++ < 256) {
            std::vector<char> data = protocol_data();
            socket.send_to(boost::asio::buffer(data), server_endpoint);
        }

    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
