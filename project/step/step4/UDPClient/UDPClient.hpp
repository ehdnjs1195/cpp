#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

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

class UDPClient
{
private:
    /*socket*/
    boost::asio::io_service _io_service;
    boost::asio::ip::udp::socket _socket;
    struct protocol{
        int InterID;
        std::vector<int> phase_time;
        std::vector<int> pahse_level;
        std::vector<int> level_cycle;
        std::vector<int> level_hour;
        std::vector<int> level_min;
        std::vector<int> level_id;
    };
    /* json database */
    protocol _prot;
    /* data of protocol database */
    std::vector<int> _jsonLevelHour;
    std::vector<int> _jsonLevelMin;
    std::vector<int> _jsonPhaseTime;
    std::vector<int> _jsonLevelCycle;
    std::vector<int> _jsonLevelId;

    std::vector<int> _partPhaseTime;
public:
    UDPClient();
    ~UDPClient();

    void loopPhase();
    void getPhaseData(const protocol& prot);
    void makePacket(const int& inter_id, const int& seq_no,
            const int& opcode, const int& phase);
    void sendPacket(const std::vector<char>& packet);
};


#endif   /* UDP_CLIENT_H_ */