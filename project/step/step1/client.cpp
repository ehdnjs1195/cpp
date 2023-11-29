#include <iostream>
#include <boost/asio.hpp>
#include <iomanip>
#include <sstream>
#include <vector>
using boost::asio::ip::udp;
std::string protocol_data(){
    // int data = 0x0003000c140002010102011a;
    static long data = 0x0003000c1400;
    // 6번째 바이트에 1을 더하기
    int mask = 0xFF ;  // 6번째 바이트에 해당하는 비트를 마스크
    int sixthByte = (data & mask) ;  // 현재 6번째 바이트의 값
    sixthByte = (sixthByte + 1) % 256;  // 1을 더하고, 255를 넘으면 0으로 되돌림
    data &= ~mask;  // 기존 6번째 바이트를 0으로 초기화
    data |= (sixthByte );  // 새로운 6번째 바이트 설정

    // data를 16진수 문자열로 변환하여 반환
    std::stringstream ss;
    ss << std::hex << std::setw(12) << std::setfill('0') << data;
    return ss.str();
}
std::vector<char> protocol_data2(){
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
        while(count++ < 5) {
            // std::string message = protocol_data();
            std::vector<char> message = protocol_data2();
            socket.send_to(boost::asio::buffer(message), server_endpoint);
        }

    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
