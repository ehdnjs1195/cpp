#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void worker(int& result, std::mutex& m) {
    for(int i=0; i<10000; i++) {
        // lock 생성 시에 m.lock() 을 실행한다고 보면 된다.
        std::lock_guard<std::mutex> lock(m);
        result += 1;

        // scope 를 빠져 나가면 lock 이 소멸되면서 m 을 알아서 unlock 한다.
        // unlock을 제대로 호출하지 못하면 다른 쓰데드들도 작업을 못하게 되는 상황이 생긴다. 이를 데드락이라고 한다.
    }
}

int main() {
    int counter = 0;
    std::mutex m;

    std::vector<std::thread> workers;
    for(int i=0; i<4; i++) {
        workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
    }
    for(int i=0; i<4; i++){
        workers[i].join();
    }

    std::cout << "Counter 최종 합: " << counter << std::endl;

}