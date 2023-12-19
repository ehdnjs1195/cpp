#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_
// #pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
// #include <mutex>

class UDPServer
{
public:
    UDPServer();
    ~UDPServer();
    bool initServer();

    bool disconnect();
private:
    bool session();

    boost::asio::io_service _ioService;
    boost::asio::ip::udp::socket _socket;
    unsigned char _buffer[1024];
    int _bufferSize;
    bool _isServerRun;
    std::thread _serverThread;
};

#endif  /* UDP_SERVER_H_ */