#include "UDPClient.h"
// 봉석님 테스트 서버 10.30.8.83 | 12001
#define SERVER_IP "127.0.0.1"
#define JSON_FILE_NAME "protocol.json"
constexpr int SERVER_PORT = 8889;

UDPClient::UDPClient()
    : _socket(_ioService),
      _isClientRun(false)
{
    this->initJsonData(JSON_FILE_NAME);
    this->connect();
}

UDPClient::~UDPClient()
{
    this->disconnect();
}

bool UDPClient::connect()
{
    // this->disconnect();
    try
    {
        this->_isClientRun = true;
        this->_socket = boost::asio::ip::udp::socket(this->_ioService, boost::asio::ip::udp::v4());
        this->_endPoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(SERVER_IP), SERVER_PORT);
        this->_clientThread = std::thread(&UDPClient::loopPhase, this);

        std::cout << "[UDPClient] Client start. " << std::endl;
        return true;
    }
    catch (const std::exception& error){
        std::cout << error.what() << std::endl;
        return false;
    }
}

bool UDPClient::disconnect()
{
    if(this->_isClientRun == false)
    {
        std::cout << "[UDPClient] Client is not exist. " << std::endl;
        return false;
    }
    try
    {
        if (this->_clientThread.joinable() == true)
            this->_clientThread.join();
        if (this->_socket.is_open())
            this->_socket.close();
        std::cout << "[UDPClient] disconnect successfully. " << std::endl;
        return true;
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return false;
    }
}
bool UDPClient::getPartPhaseTime()
{
    auto sum = 0;
    auto phaseSize = this->protocol.phaseTime.size() / this->protocol.levelId.size();
    for(auto i = 0; i < this->protocol.phaseTime.size(); i++)
    {
        sum += this->protocol.phaseTime[i];
        this->_partPhaseTime.push_back(sum);
        if((i + 1) % phaseSize == 0)
            sum = 0;
    }
    if(this->_partPhaseTime.size() == 0) return false;
    return true;
}

bool UDPClient::initJsonData(const std::string& json_file_name)
{
    try
    {
        boost::property_tree::ptree props;
        boost::property_tree::ptree plan;
        boost::property_tree::ptree level;
        boost::property_tree::ptree phase;
        boost::property_tree::read_json(json_file_name, props); // 예외처리?
        // InterID 값 가져오기
        auto InterID = props.get<int>("InterID");
        this->protocol.InterID = InterID;

        // Plan 배열 순회
        for (const auto &plan : props.get_child("Plan"))
        {
            // Level 배열 순회
            for (const auto &level : plan.second.get_child("Level"))
            {
                // level_hour
                auto hour = level.second.get<int>("hour");
                this->protocol.levelHour.push_back(hour);
                // level_min
                auto min = level.second.get<int>("min");
                this->protocol.levelMin.push_back(min);
                // level_cycle
                auto cycle = level.second.get<int>("cycle");
                this->protocol.levelCycle.push_back(cycle);
                // level_id
                auto id = level.second.get<int>("ID");
                this->protocol.levelId.push_back(id);

                // phase 배열 순회
                for (const auto &phase : level.second.get_child("phase"))
                {
                    // RingA 값 가져오기
                    auto RingA = phase.second.get<int>("RingA");
                    this->protocol.phaseTime.push_back(RingA);
                    // phase_level
                    auto num = phase.second.get<int>("num");
                    this->protocol.pahseLevel.push_back(num);
                }
            }
        }
    }
    catch (const boost::property_tree::json_parser_error& jsonError)
    {
        std::cerr << "[UDPClient] Error while reading JSON file: " << jsonError.what() << std::endl;
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << "[UDPClient] An error occurred: " << e.what() << std::endl;
        return false;
    }
    this->getPartPhaseTime();
    return true;
}
void UDPClient::loopPhase()
{
    auto level_size = this->protocol.levelId.size();
    auto phase = 0;
    auto seq_no = 0;
    auto phase_level = 0;
    auto opcode = 0;
    auto is_first_phase_known = false;
    auto cycle_over_flag = false;
    auto is_last_level_time = false;
    auto exchange_to_sec = 60;
    this->protocol.levelHour.push_back(this->protocol.levelHour[0]);
    int phaseSize = this->protocol.phaseTime.size() / this->protocol.levelId.size();
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));   // 1초

        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        auto *time = std::localtime(&currentTime);   // 현재 시간 정보를 갖고있는 객체
        auto curr_hour = time->tm_hour;
        auto curr_min = time->tm_min;
        auto curr_sec = time->tm_sec;
        std::cout << "hour: " << curr_hour << " | min: " << curr_min << " | sec: " << curr_sec << std::endl;

        for(auto i=0; i<level_size; i++)
        {    // level 1~4
            if(i == level_size-1) is_last_level_time = true;    // 마지막 수준이라면

            // 수준에 따른 hour, min을 반영할 수 있도록 계산
            auto prev_time = this->protocol.levelHour[i] * exchange_to_sec + this->protocol.levelMin[i];
            auto post_time = this->protocol.levelHour[i+1] * exchange_to_sec + this->protocol.levelMin[i+1];
            auto curr_time = curr_hour * exchange_to_sec + curr_min;
            if(prev_time <= curr_time && (post_time > curr_time || is_last_level_time))
            {    // level 구간 확인
                auto sec = (curr_hour - this->protocol.levelHour[i]) * exchange_to_sec * exchange_to_sec + curr_min * exchange_to_sec + curr_sec; // 구간내 시간을 sec로 변환
                if(seq_no == 256) seq_no = 0;             // seqNo는 0부터 255까지

                phase = (sec % this->protocol.levelCycle[i]) + 1;    // 구간 내에서의 시간, 곧 phase
                if(!is_first_phase_known)   // 처음 phase 찾기
                {
                    for(auto j=0; j < phaseSize; j++)
                    {
                        if(phase >= this->protocol.phaseTime[j + (i * phaseSize)])
                            phase_level = j+1;
                    }
                    is_first_phase_known = true;
                }

                std::cout << "phase: " << phase << " | this->protocol.phaseTime: " << this->protocol.phaseTime[(phase_level) + phaseSize * (this->protocol.levelId[i]-1)]
                << " | level_id: " << this->protocol.levelId[i] << " | phase_level: " << phase_level +1 << " | secNo: " << seq_no <<std::endl;

                if(phase == this->protocol.phaseTime[(phase_level) + phaseSize*(this->protocol.levelId[i]-1)]) {
                    phase_level++;
                    if(phase_level % phaseSize == 0) {
                        opcode = 0x24;                  // 사이클이 끝났을 때
                        this->makePacket(this->protocol.InterID, seq_no++, opcode, phase_level);
                        opcode = 0x22;                  // 사이클이 시작할 때
                        this->makePacket(this->protocol.InterID, seq_no++, opcode, phase_level);
                    }
                    opcode = 0x14;
                    this->makePacket(this->protocol.InterID, seq_no++, opcode, phase_level);
                }
                if(phase_level == phaseSize) phase_level = 0;  //phase_level 초기화
            }
            is_last_level_time = false;
        }
    }
    this->_isClientRun = false;
}
void UDPClient::makePacket(const int& inter_id, const int& seq_no, const int& opcode, const int& phase)
{
    std::vector<char> packet;
    // 1~2 inter_id
    packet.push_back((inter_id >> 8) & 0xFF);
    packet.push_back(inter_id & 0xFF);
    // 3~4 size
    packet.push_back(0x00);
    packet.push_back(0x0c);
    // 5 OPCODE
    packet.push_back(opcode & 0xFF);
    // 6 seq No
    packet.push_back(seq_no & 0xFF);
    // 7 phase info
    packet.push_back(0x02);
    packet.push_back(0x01); // RingA
    packet.push_back(phase & 0xFF);
    packet.push_back(0x02); // RingB
    packet.push_back(phase & 0xFF);
    // 8 LRC check
    std::uint8_t check_lrc = 0x00;
    for(int i=0; i<packet.size(); i++){
        check_lrc ^= packet[i]; // 전체 XOR 연산
    }
    packet.push_back(check_lrc);

    this->sendPacket(packet);
}

void UDPClient::sendPacket(const std::vector<char>& packet)
{
    try
    {
        boost::system::error_code error;
        size_t send_bytes = this->_socket.send_to(boost::asio::buffer(packet), this->_endPoint, 0, error);
        std::cout << "[UDPClient] send packet. " << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "[UDPClient] sending packet failed. " << std::endl;
        std::cerr << e.what() << '\n';
    }
}