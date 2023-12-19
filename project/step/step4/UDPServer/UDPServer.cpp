#include "UDPServer.h"
constexpr int PORT_NUM = 8889;

UDPServer::UDPServer()
    : _socket(_ioService),
      _isServerRun(false)
{
    this->initServer();
}

UDPServer::~UDPServer()
{
    this->disconnect();
}

bool UDPServer::initServer()
{
    // this->disconnect();
    try
    {
        this->_isServerRun = true;
        this->_socket = boost::asio::ip::udp::socket
                (this->_ioService,
                boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT_NUM));
        this->_serverThread = std::thread(&UDPServer::session, this);

        std::cout << "[UDPServer] server start. " << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));    // ###

        return true;
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return false;
    }
}

bool UDPServer::disconnect()
{
    if (this->_isServerRun == false)
    {
        std::cout << "[UDPServer] Server is not exist. " << std::endl;
        return false;
    }
    try
    {
        if (this->_serverThread.joinable() == true)
            this->_serverThread.join();
        if(this->_socket.is_open())
            this->_socket.close();
        std::cout << "[UDPServer] disconnect successfully. " << std::endl;
        return true;
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return false;
    }
}

bool UDPServer::session()
{
    boost::asio::ip::udp::endpoint client_endpoint;
    boost::system::error_code error;
    while(true)
    {
        unsigned char buffer[1024];
        auto bytes_received = this->_socket.receive_from(boost::asio::buffer(buffer), client_endpoint, 0 ,error);
        if(error){
            std::cerr << "[UDPServer] receive from error: " << error.message() << std::endl;
            continue;
        }
        std::vector<int> packet(buffer, buffer + bytes_received);
        std::cout << "[UDPServer] Received from [" << client_endpoint.address() << "|" << client_endpoint.port() << "]: " ;
        for (int value : packet)
        {
            printf("%02X ", value);
        }
        std::cout << std::endl;
    }
    this->_isServerRun = false;
}