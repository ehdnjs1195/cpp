#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono> // 추가
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
// #include <boost/foreach.hpp>
// #include <boost/json/src.hpp>

using boost::asio::ip::udp;

std::vector<char> protocol_packet(){
    static std::vector<char> data = {0x00, 0x03, 0x00, 0x0c, 0x14, 0x00};
    data[5] = (data[5] + 1) % 256; // 6번째 byte 1 더하기

    return data;
}
std::vector<int> get_phase_time(){
    std::vector<int> phase_time;
    boost::property_tree::ptree props, plan, level, phase;
    boost::property_tree::read_json("protocol.json", props);

    // InterID 값 가져오기
    int InterID = props.get<int>("InterID");
    std::cout << "InterID: " << InterID << std::endl;

    // Plan 배열 순회
    for (const auto &plan : props.get_child("Plan")) {
        // Level 배열 순회
        for (const auto &level : plan.second.get_child("Level")) {
            // phase 배열 순회
            for (const auto &phase : level.second.get_child("phase")) {
                // RingA 값 가져오기
                int RingA = phase.second.get<int>("RingA");
                phase_time.push_back(RingA);
                // std::cout << "RingA: " << RingA << std::endl;
            }
        }
    }
    return phase_time;

}
int main() {
    try{
        std::vector<int> phase_time;
        phase_time = get_phase_time();
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::v4());
        // 봉석님 테스트 서버 10.30.8.83 | 12001
        udp::endpoint server_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888);
        int count = 0;
        for(auto time : phase_time) {
            std::cout << time << " ";
        }
        std::cout << std::endl;
        while(count++ < 256) {
            std::vector<char> data = protocol_packet();
            boost::system::error_code error;
            std::cout << "send to server!" << std::endl; 
            size_t send_bytes = socket.send_to(boost::asio::buffer(data), server_endpoint, 0, error);

            if(send_bytes == 0) {
                std::cerr << "send 실패: " << error << std::endl;
                return 0;
            }

            // 각 phase만큼 시간 부여(임시)
            std::this_thread::sleep_for(std::chrono::milliseconds(phase_time[count/phase_time.size()]));
        }

    } catch(std::exception& e) { // 예외 객체에 대한 참조로 수정
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
