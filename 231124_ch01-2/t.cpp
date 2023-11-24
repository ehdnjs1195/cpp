#include <iostream>
#include <string>
#include "A.hpp"

namespace A{
    void move() {
        std::cout << "A move()!" << std::endl;
        std::cout << sleep::status::humidity << std::endl;
    }
    void stop() {
        std::cout << "A stop()" << std::endl;
    }
    namespace custom{
        void move() {
            std::cout << "A custom move()!" << std::endl;
        }
    }
}

// namespace B{
//     void move() {
//         std::cout << "B move()!" <<std::endl;
//     }
// }
// void move() {
//     std::cout << "그냥 move()" << std::endl;
// }
int main() {
    A::move();
    A::custom::move();
    move();
    // B::move();
    
    sleep::sleeping();
    sleep::status::curr_status();

}