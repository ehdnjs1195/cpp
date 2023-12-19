// #ifndef UDP_CLIENT_H_
// #define UDP_CLIENT_H_
#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <chrono>   // 시간
#include <ctime>    // 시간구하기
// #include <future>   // async로 비동기처리 or thread-condition_variable 처리
#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class UDPClient
{
public:
    UDPClient();
    ~UDPClient();

    bool connect();

    bool disconnect();

    bool initJsonData(const std::string& json_file_name);

private:
    void loopPhase();

    void makePacket(const int& inter_id, const int& seq_no, const int& opcode, const int& phase);

    bool getPartPhaseTime();

    void sendPacket(const std::vector<char>& packet);
    /* socket */
    boost::asio::io_service _ioService;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _endPoint;
    /* server address info */
    int _port;
    std::string _serverIP;
    /* json database struct */
    struct Protocol
    {
        int InterID;
        std::vector<int> phaseTime;
        std::vector<int> pahseLevel;
        std::vector<int> levelCycle;
        std::vector<int> levelHour;
        std::vector<int> levelMin;
        std::vector<int> levelId;
    };
    Protocol protocol;
    /* logic data vector */
    std::vector<int> _partPhaseTime;

    std::atomic_bool _isClientRun;
    std::thread _clientThread;
};


// #endif   /* UDP_CLIENT_H_ */