#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])    // argument로 서버의 주소를 입력을 받고 있다.
{
    try 
    {
        if(argc != 2)   // argc가 없으면 종료.
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        tcp::iostream stream(argv[1], std::to_string(int(13))); //  argv[1]로 입력한 ip주소가 들어옴, port number 13
        if(!stream)
        {
            std::cout << "Unable to connet: " << stream.error().message() << std::endl;
            return 1;
        }

        // send message to server
        stream << "Hello from client";
        stream << std::endl;    // send new-line to end receiver'stream getline

        // receive message from server
        std::string line;
        std::getline(stream, line);
        std::cout << line << std::endl;
    }
    catch(std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
} 