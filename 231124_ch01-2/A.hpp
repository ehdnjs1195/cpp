#include <string>
#include <iostream>

void move()
{
    std::cout << "in A.hpp move()" << std::endl;
}
namespace sleep{
    int time;
    std::string address;
    void sleeping() {
        std::cout << "sleeping..." << std::endl;
    }

    namespace status {
        int temperature = 37;
        int humidity = 53;
        void curr_status(){
            std::cout << "temp: " << temperature << " || humidity: " << humidity << std::endl;
        }
    }

    class T {
        public:
        std::string class_name = "T";
        void print_name() {
            std::cout << "my name is " << class_name << std::endl;
        }
    };
    
}