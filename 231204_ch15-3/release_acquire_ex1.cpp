#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

void producer(std::atomic<bool>* is_ready, int* data) {
    *data = 10;
    is_ready->store(true, std::memory_order_release);
    // release는 이전의 코드가 이후로 넘어갈 수 없다.
}

void consumer(std::atomic<bool>* is_ready, int* data) {
    // data 가 준비될 때 까지 기다린다.
    while (!is_ready->load(std::memory_order_acquire)) {
    }
    // acquire는 이 후의 코드가 이전으로 넘어올 수 없다.
    std::cout << "Data : " << *data << std::endl;
}

/*
    따라서 release - acquire 사이로는 코드의 재배치되지 않기 때문에 동기화를 수행하는 것을 볼 수 있다.
*/

int main() {
    std::vector<std::thread> threads;

    std::atomic<bool> is_ready(false);
    int data = 0;

    threads.push_back(std::thread(producer, &is_ready, &data));
    threads.push_back(std::thread(consumer, &is_ready, &data));

    for (int i = 0; i < 2; i++) {
        threads[i].join();
    }
}