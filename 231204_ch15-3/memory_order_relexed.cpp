#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>
#include <iostream>

using std::memory_order_relaxed;

void t1(std::atomic<int>* a, std::atomic<int>* b) {
    b->store(1, memory_order_relaxed);      // b = 1 (쓰기)
    int x = a->load(memory_order_relaxed);  // x = a (읽기)

    printf("x : %d \n", x);
}

void t2(std::atomic<int>* a, std::atomic<int>* b) {
    a->store(1, memory_order_relaxed);      // a = 1 (쓰기)
    int y = b->load(memory_order_relaxed);  // y = b (읽기)

    printf("y : %d \n", y);
}
void diff_res() {   // 1. x, y가 예상치 못한 결과가 나올 수 있음.
    std::vector<std::thread> threads;

    std::atomic<int> a(0);
    std::atomic<int> b(0);

    threads.push_back(std::thread(t1, &a, &b));
    threads.push_back(std::thread(t2, &a, &b));

    for (int i = 0; i < 2; i++) {
        threads[i].join();
    }
    /*
        memory_order_relexed는 메모리 연산들 사이에서 어떠한 제약조건도 없음.
        따라서 메모리 연산을 CPU 마음대로 재배치 할 수 있다.

        예를들어
        int x = a->load(memory_order_relaxed);  // x = a (읽기)
        b->store(1, memory_order_relaxed);      // b = 1 (쓰기)
        와 같이 재배치될 수 있고, 이 경우 x, y 모두 0이 될 수도 있다.
    */
}

void worker(std::atomic<int>* counter) {
  for (int i = 0; i < 10000; i++) {
    /*
        다른 연산들 수행 ***
        
        비록 다른 메모리 연산들 보다 counter ++ 이 늦게 된다고 하더라도 
        결과적으로 증가 되기만 하면 문제 될게 없기 때문입니다.
    */

    counter->fetch_add(1, memory_order_relaxed);    // counter++ 과 일치하지만, 원자적으로 1을 더하고 다시 결과를 쓴다.
  }
}
void nomatter_res(){    // 2. 결과만 잘 나온다면 상관 없다.
    std::vector<std::thread> threads;

    std::atomic<int> counter(0);

    for (int i = 0; i < 4; i++) {
        threads.push_back(std::thread(worker, &counter));
    }

    for (int i = 0; i < 4; i++) {
        threads[i].join();
    }

    std::cout << "Counter : " << counter << std::endl;
}

int main() {
    // diff_res();
    nomatter_res();
}