#include <iostream>
#include <thread>
using std::thread;

void func1() {
    for (int i = 0; i < 10; i++) {
        std::cout << "쓰레드 1 작동중! \n";
    }
}
void func2() {
    for (int i = 0; i < 10; i++) {
        std::cout << "쓰레드 2 작동중! \n";
    }
}
void func3() {
    for (int i = 0; i < 10; i++) {
        std::cout << "쓰레드 3 작동중! \n";
    }
}

void thread_join(){
    thread t1(func1);
    thread t2(func2);
    thread t3(func3);
    // join으로 쓰레드를 main에 묶어두어야 쓰레드가 종료되고, 메인함수가 종료된다.
    t1.join();
    t2.join();
    t3.join();
}
void thread_detach() {
    thread t1(func1);
    thread t2(func2);
    thread t3(func3);
    // detach는 해당 쓰레드를 실행시킨 후 잊어버리는 것이다. 쓰레드는 알아서 백그라운드에서 돌아간다.
    t1.detach();
    t2.detach();
    t3.detach();
    // 쓰레드를 detach 하게 된다면 main 함수에서는 더이상 쓰레드들이 종료될 때 까지 기다리지 않습니다.
    // 실제로 실행 시켜보면, main이 종료되어 버려서 쓰레드가 아예 실행이 되지 않을 수도 있고, 중간에 프로세스가 종료될 수도 있다.
}
int main() {
    // thread_join();
    thread_detach();

    std::cout << "메인 함수 종료 \n";
}