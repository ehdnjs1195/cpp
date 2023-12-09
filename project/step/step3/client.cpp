#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono>   // 시간
#include <ctime>    // 시간구하기
#include <future>   // async로 비동기처리 or thread-condition_variable 처리
#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using boost::asio::ip::udp;
struct protocol{
    int InterID;
    std::vector<int> phase_time;
    std::vector<int> level_cycle;
    std::vector<int> level_time;
    std::vector<int> level_id;
};

void make_packet(int interID, int seqNo, int phase);
void send_packet(std::vector<char> packet);
void loop_phase();
void get_phase_data(protocol& prot);


int main() {
    try{
        std::thread loop_thread(loop_phase);

        loop_thread.join();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
void loop_phase(){
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *time = std::localtime(&currentTime);   // 현재 시간 정보를 갖고있는 객체
    // json database
    protocol prot;
    get_phase_data(prot);
    // data of protocol database 
    std::vector<int> db_level_time = prot.level_time;
    std::vector<int> db_phase_time = prot.phase_time;
    std::vector<int> db_level_cycle = prot.level_cycle;
    std::vector<int> db_level_id = prot.level_id;
    int level_size = prot.level_id.size();
    int phase = 0, seqNo = 0;
    while(true) {
        // 실시간
        int curr_hour = time->tm_hour;
        int curr_min = time->tm_min;
        int curr_sec = time->tm_sec;
        std::cout << "hour: " << curr_hour << " | min: " << curr_min << " | sec: " << curr_sec << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        for(int i=0; i<level_size; i++){    // level 1~3
            if(i==level_size-1) break;  // 마지막 level이 되면
            std::cout << "for문" << std::endl;
            if(db_level_time[i] <= curr_hour && db_level_time[i+1] > curr_hour){          
                std::cout << "check1" << std::endl;
                int sec = (curr_hour - db_level_time[i]) * 60 * 60 
                            + curr_min * 60
                            + curr_sec;
                seqNo = sec / db_level_cycle[i];        // 구간 내의 사이클, 곧 seqNo  
                phase = (sec % db_level_cycle[i]) + 1;    // 구간 내의 현시, 곧 phase

                int phase_size = db_phase_time.size() / db_level_id.size(); // phase 개수
                
                for(int j=0; j<phase_size; j++) {   
                    std::cout << "check2" << " | seqNo: " << seqNo << " | phase: " << phase <<" | i: "<< i <<" | db_level_id[i]: "<< db_level_id[i] << " | (j%phase_size) + 3*(db_level_id[i]-1): " <<(j%phase_size) + 3*(db_level_id[i]-1) << " | db_phase_time[(j%phase_size) + 3*(db_level_id[i]-1)]: "<< db_phase_time[(j%phase_size) + 3*(db_level_id[i]-1)] <<" | db_phase_time: " << db_phase_time[j] <<std::endl;
                    if(phase == db_phase_time[(j%phase_size) + 3*(db_level_id[i]-1)]){    // 각 수준별(level) 주기, 현시의 개수가 다르므로
                        std::cout << "make_packet() 함수 실행 전. " << std::endl;
                        std::async([&](){make_packet(prot.InterID, seqNo, j+1);}).get();      // 현시가 되었을 때 패킷정보 전달 및 비동기적함수 호출
                    }
                }
            }
        }
        // 마지막 level
        int sec = (curr_hour - db_level_time[level_size-1]) * 60 * 60 
                    + curr_min * 60
                    + curr_sec;
        seqNo = sec / db_level_cycle[level_size-1];        // 구간 내의 사이클, 곧 seqNo  
        phase = sec % db_level_cycle[level_size-1] + 1;    // 구간 내의 현시, 곧 phase

        int phase_size = db_phase_time.size() / db_level_id.size(); // phase 개수
        for(int i=0; i<phase_size; i++) {   
            if(phase == db_phase_time[(i%phase_size) + db_level_id[level_size-1] - 1]){    // 각 수준별(level) 주기, 현시의 개수가 다르므로
                std::async([&](){make_packet(prot.InterID, seqNo, i+1);}).get();      // 현시가 되었을 때 패킷정보 전달 및 비동기적함수 호출
            }
        }

        // if(db_level_time[0] <= curr_hour && db_level_time[1] > curr_hour){          // 6 ~ 10   level_1
        //     int sec = (curr_hour - db_level_time[0]) * 60 * 60 
        //                 + curr_min * 60
        //                 + curr_sec;
        //     seqNo = sec / db_level_cycle[0];        // 구간 내의 사이클, 곧 seqNo  
        //     phase = sec % db_level_cycle[0] + 1;    // 구간 내의 현시, 곧 phase

        //     int phase_size = db_phase_time.size() / db_level_id.size(); // phase 개수
        //     for(int i=0; i<phase_size; i++) {   
        //         if(phase == db_phase_time[(i%phase_size) + db_level_id[0] - 1]){    // 각 수준별(level) 주기, 현시의 개수가 다르므로
        //             std::async([&](){make_packet(prot.InterID, seqNo, i+1);});      // 현시가 되었을 때 패킷정보 전달 및 비동기적함수 호출
        //         }
        //     }
        //     // if(phase == db_phase_time[0]){          // 각 수준별(level) 주기, 현시의 개수가 다르므로
        //     //     std::async([](){send_packet();});
        //     // } else if(phase == db_phase_time[1]){
        //     //     std::async([](){send_packet();});
        //     // } else if(phase == db_phase_time[2]){
        //     //     std::async([](){send_packet();});
        //     // }
        // } else if(db_level_time[1] <= curr_hour && db_level_time[2] > curr_hour){   // 10 ~ 16  level_2
            
        // } else if(db_level_time[2] <= curr_hour && db_level_time[3] > curr_hour){   // 16 ~ 22  level_3

        // } else {                                                                    // 22 ~ 6   level_4
            
        // }
        
    }
}

void get_phase_data(protocol& prot){
    std::cout << "get_phase_data() 실행" << std::endl;
    boost::property_tree::ptree props, plan, level, phase;
    boost::property_tree::read_json("protocol.json", props);
    // InterID 값 가져오기
    int InterID = props.get<int>("InterID");
    prot.InterID = InterID;
    // std::cout << "InterID: " << InterID << std::endl;

    // Plan 배열 순회
    for (const auto &plan : props.get_child("Plan")) {
        // Level 배열 순회
        for (const auto &level : plan.second.get_child("Level")) {
            // level_time
            int time = level.second.get<int>("time");
            prot.level_time.push_back(time);
            // level_cycle
            int cycle = level.second.get<int>("cycle");
            prot.level_cycle.push_back(cycle);
            // level_id
            int id = level.second.get<int>("ID");
            prot.level_id.push_back(id);
            // phase 배열 순회
            for (const auto &phase : level.second.get_child("phase")) {
                // RingA 값 가져오기
                int RingA = phase.second.get<int>("RingA");
                prot.phase_time.push_back(RingA);
                // std::cout << "RingA: " << RingA << std::endl;
            }
        }
    }
}
void make_packet(int interID, int seqNo, int phase){
    std::cout << "make_packet() 실행" << std::endl;
    std::vector<char> packet;
    // 1~2 interID
    packet.push_back((interID >> 8) & 0xFF);    
    packet.push_back(interID & 0xFF);
    // 3~4 size
    packet.push_back(0x0c);
    // 5 OPCODE
    packet.push_back(0x14);
    // 6 seq No
    packet.push_back(seqNo & 0xFF);
    // 7 phase info
    packet.push_back(0x02);
    packet.push_back(0x01); // RingA
    packet.push_back(phase & 0xFF);
    packet.push_back(0x02); // RingB
    packet.push_back(phase & 0xFF);
    // 8 LRC
    std::uint8_t check_lrc = 0x00;
    for(int i=0; i<packet.size(); i++){
        check_lrc ^= packet[i]; // 전체 XOR 연산
    }
    packet.push_back(check_lrc);

    send_packet(packet);
    
}

void send_packet(std::vector<char> packet){
    try{
        std::cout << "send_packet() 실행" << std::endl;
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::v4());
        udp::endpoint server_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888);

        boost::system::error_code error;
        size_t send_bytes = socket.send_to(boost::asio::buffer(packet), server_endpoint, 0, error);
        if(error) {
            std::cerr << "send 실패: " << error.what() << std::endl;
            return ;
        }
        std::cout << "send to server!" << std::endl;

    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
