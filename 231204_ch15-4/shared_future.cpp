#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using std::thread;

void runner(std::shared_future<void> start, int count) {
    start.get();    // 복사본들이 모두 같은 객체를 공유하기 때문에 각 다른 쓰레드에서 get을 할 수 있다.
    std::cout << "출발! " << count << std::endl;
}

int main() {
    std::promise<void> p;
    std::shared_future<void> start = p.get_future();    // future 와는 다르게 복사가 가능하고, 복사본들이 모두 같은 객체를 공유하게 됩니다. 따라서 레퍼런스나 포인터로 전달할 필요가 없습니다.
    int count=0;
    thread t1(runner, start, ++count);
    thread t2(runner, start, ++count);
    thread t3(runner, start, ++count);
    thread t4(runner, start, ++count);

    // 참고로 cerr 는 std::cout 과는 다르게 버퍼를 사용하지 않기 때문에 터미널에
    // 바로 출력된다.
    std::cerr << "준비...";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cerr << "땅!" << std::endl;

    p.set_value();

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}