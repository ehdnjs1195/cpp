#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() 
{
    try{
        boost::asio::io_service io_service; 

        tcp::endpoint endpoint(tcp::v4(), 8888);          // 엔드 포인트 설정: IPv4, port번호
        tcp::acceptor acceptor(io_service, endpoint);     // acceptor 생성

        std::cout << "Server started" << std::endl;

        for(;;) 
        {
            // const std::string message_to_send = "Hello From Server";

            boost::asio::ip::tcp::iostream stream;  // 통신 스트림 객체


            boost::system::error_code ec;
            acceptor.accept(*stream.rdbuf(), ec);   // accept()함. stream 으로 readbuffer

            // std::cout << "check 2" << std::endl;

            // acceptor로 인해 ec가 null 값이 아니고 값이 들어왔다면 클라이언트가 제대로 접속했다는 뜻이 됨.
            if(!ec) //TODO: How to take care of multiple clients? Multi-threading?
            {
                // receive message from client 
                std::cout << "message: " ;
                std::string line;
                std::getline(stream, line);    
                std::cout << line << std::endl;

                // send message to client
                // stream << message_to_send;  // stream에 보낼 메세지 넘겨주기.
                // stream << std::endl;        // send std::endl to end getline of client

            }
        }
    } 
    catch(std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}