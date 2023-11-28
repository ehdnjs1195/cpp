#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::udp;

int main() {
    try{
        boost::asio::io_service io_service;
        udp::socket socket(io_service, udp::v4());

        udp::endpoint server_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888);

        std::string message = "Hello, UDP Server!";
        socket.send_to(boost::asio::buffer(message), server_endpoint);

    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
