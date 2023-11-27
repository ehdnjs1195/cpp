#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <vector>
#include <mutex>

using namespace std;
void ex1() {
    std::thread t1 = std::thread([]() {
        cout << "쓰레드 t1: " << std::this_thread::get_id() << endl;
        while(true) 
        {
        }
    }); // 1. 함수 포인터, 2. std::function, 3. 람다 함수 을 사용할 수 있다.

    t1.join();  // t1이 끝날 때 까지 프로세스가 종료하지 않고 기다려달라는 의미(메인함수 대기)
}
int main() 
{
    const int num_pro = std::thread::hardware_concurrency();
    // cout << std::thread::hardware_concurrency() << endl;    // 내 컴퓨터 cpu 24까지 가능

    cout << "메인 쓰레드: " <<std::this_thread::get_id() << endl; // 지금 사용하는 쓰레드의 아이디

    vector<std::thread> my_threads;
    my_threads.resize(num_pro); // 멀티스레딩하기. 
    int thread_count=0;
    for(auto &e : my_threads) {
        e = std::thread([&]() {
            cout << "쓰레드" << thread_count++ << ": " << std::this_thread::get_id() << endl;
            while(true) {}
        });
    }
    for(auto & e :my_threads) { // 쓰레드들 join해주기. => 실제 예제를 시작하고, 작업 관리자 성능을 살펴보면 cpu 이용률이 100%로 올라간다.
        e.join();
    }

}