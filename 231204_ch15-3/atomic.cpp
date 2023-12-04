#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void worker(std::atomic<int>& counter) {
    for(int i=0; i< 10000; i++){
        counter++;
    }
}

int main() {
    std::atomic<int> counter(0);    // 템플릿 인자로 원자적으로 만들고 싶은 타입을 전달
    
    std::vector<std::thread> workers;
    for(int i=0; i < 4; i++){
        workers.push_back(std::thread(worker, std::ref(counter)));
    }
    for(int i=0; i<4; i++){
        workers[i].join();
    }

    std::cout << "Counter 최종 값: " << counter << std::endl;
    std::cout << "is lock free ? : " << std::boolalpha << counter.is_lock_free() << std::endl;  // is_lock_free() 는 atomic 객체의 연산들이 과연 정말 원자적으로 구현되는지 확인할 수 있는 함수있다.
}