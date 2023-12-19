// #include "UDPClient/UDPClient.h"
#include "UDPClient/UDPClient.cpp"
// #include "UDPServer/UDPServer.h"
#include "UDPServer/UDPServer.cpp"

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        if (argv[1] == std::string("server"))
        {
            UDPServer server;
        }
        else if (argv[1] == std::string("client"))
        {
            UDPClient client;
        }
    }
    return 0;
}