#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono>   // 시간
#include <ctime>    // 시간구하기
#include <future>   // async로 비동기처리 or thread-condition_variable 처리
#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
// 봉석님 테스트 서버 10.30.8.83 | 12001
// #define SERVER_IP "10.30.8.83"
// #define SERVER_PORT 12001
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8889

using boost::asio::ip::udp;
struct protocol{
    int InterID;
    std::vector<int> phase_time;
    std::vector<int> pahse_level;
    std::vector<int> level_cycle;
    std::vector<int> level_time;
    std::vector<int> level_id;
};

void make_packet(int interID, int seqNo, int opcode, int phase);
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
    int phase_level=0;  // 현시 저장 변수
    bool is_first_phase_flag = false;   // 현재 현시를 아는지
    int phase_size = db_phase_time.size() / db_level_id.size(); // phase 개수
    db_level_time.push_back(db_level_time[0]);  // 마지막 원소로 처음 level시간을 넣어주기
    int opcode = 0; //opcode
    bool cycle_over_flag = false;
    bool is_last_level_time_flag= false;   
   
    std::vector<int> part_phase_time;   // 현시를 파트별로 합으로 나타낸 벡터
    int sum=0;
    for(int i=0; i<db_phase_time.size(); i++) {
        sum += db_phase_time[i];
        part_phase_time.push_back(sum);
        if((i+1)%phase_size == 0) sum = 0;
    }
    std::cout << "part_phase_time: [ ";
    for(int x:part_phase_time){
        std::cout  << x << " " ;
    }
    std::cout << " ]"<<std::endl;

    while(true) {
        // 실시간
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm *time = std::localtime(&currentTime);   // 현재 시간 정보를 갖고있는 객체
        int curr_hour = time->tm_hour;
        int curr_min = time->tm_min;
        int curr_sec = time->tm_sec;
        std::cout << "hour: " << curr_hour << " | min: " << curr_min << " | sec: " << curr_sec << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));   // 1초

        for(int i=0; i<level_size; i++){    // level 1~4
            // std::cout << std::boolalpha << "i == level_size-1: " << (i == level_size-1) << std::endl;
            if(i == level_size-1) is_last_level_time_flag = true;    // 마지막 수준이라면
            if(db_level_time[i] <= curr_hour && (db_level_time[i+1] > curr_hour || is_last_level_time_flag)){    // level 구간 확인
                int sec = (curr_hour - db_level_time[i]) * 60 * 60 
                            + curr_min * 60
                            + curr_sec;                 // 구간내 시간을 sec로 변환
                if(seqNo == 256) seqNo = 0;             // seqNo는 0부터 255까지
                phase = (sec % db_level_cycle[i])+1;    // 구간 내에서의 시간, 곧 phase
                if(!is_first_phase_flag){               // 처음 phase 찾기
                    for(int j=0; j<phase_size; j++){
                        if(phase >= part_phase_time[j + (i * phase_size)]){
                            phase_level = j+1;
                        }
                    }
                    is_first_phase_flag = true;
                }
                
                std::cout << "phase: " << phase << " | part_phase_time: " << part_phase_time[(phase_level) + phase_size*(db_level_id[i]-1)] << " | level_id: " << db_level_id[i] << " | phase_level: " << phase_level +1 << " | secNo: " << seqNo <<std::endl;
                if(phase == part_phase_time[(phase_level) + phase_size*(db_level_id[i]-1)]) {
                    phase_level++;
                    if(phase_level%phase_size == 0) { 
                        opcode = 0x24;                  // 사이클이 끝났을 때
                        std::async([&](){make_packet(prot.InterID, seqNo++, opcode, (phase_level)+ 1);}).get();
                        opcode = 0x22;                  // 사이클이 시작할 때
                        std::async([&](){make_packet(prot.InterID, seqNo++, opcode, (phase_level)+ 1);}).get();
                    }
                    opcode = 0x14;
                    std::async([&](){make_packet(prot.InterID, seqNo++, opcode, (phase_level)+ 1);}).get();        // 정해진 현시가 되었을 때 비동기적으로 패킷정보 전달
                }
                if(phase_level == phase_size) phase_level = 0;  //phase_level 초기화
            }
            is_last_level_time_flag = false;
        }
    }
}

void get_phase_data(protocol& prot){
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
                // phase_level
                int num = phase.second.get<int>("num");
                prot.pahse_level.push_back(num);
            }
        }
    }
}
void make_packet(int interID, int seqNo, int opcode, int phase){    // 전달 받은 데이터로 패킷 형성
    std::vector<char> packet;
    // 1~2 interID
    packet.push_back((interID >> 8) & 0xFF);    
    packet.push_back(interID & 0xFF);
    // 3~4 size
    packet.push_back(0x00);
    packet.push_back(0x0c);
    // 5 OPCODE
    packet.push_back(opcode & 0xFF);
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

void send_packet(std::vector<char> packet){ // packet 전송 
    try{
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::v4());
        udp::endpoint server_endpoint(boost::asio::ip::address::from_string(SERVER_IP), SERVER_PORT);

        boost::system::error_code error;
        size_t send_bytes = socket.send_to(boost::asio::buffer(packet), server_endpoint, 0, error);
        if(error) {
            std::cerr << "send 실패: " << error.what() << std::endl;
            return ;
        }
        std::cout << "send to server: " << std::endl;

    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
