#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <vector>
#include <mutex>

using namespace std;
mutex mtx;  // mutual exclusion => 상호배제: 자기것만 사용할 수 있도록.
int main() {
    auto work_func = [](const string& name) 
    {
        for (int i = 0; i < 5; ++i) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            //한번에 하나의 쓰레드만 사용가능하도록 락을 걸어줌.
            mtx.lock(); // 다른 쓰레드가 들어오지 못하도록 막아줌
            cout << name << " " << std::this_thread::get_id() << " is working " << i << endl;   // 작업수행.
            mtx.unlock();   // 다시 락을 풀어줌.
        }
    };

    std::thread t1 = std::thread(work_func, "JackJack");    // 람다함수를 넣어주고, 인자를 뒤에 적어줌.
    std::thread t2 = std::thread(work_func, "Dash");

    t1.join();
    t2.join();
}