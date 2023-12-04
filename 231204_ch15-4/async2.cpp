#include <future>
#include <iostream>
#include <thread>
/*
    컴파일 하고 실행파일을 time 프로그램으로 실행하면 total 시간이 나옴.
    ex) time ./a.out
*/
int do_work(int x) {    // 3초가 걸리는 어떤 일.
    // x 를 가지고 무슨 일을 한다.
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return x;
}

void do_work_parallel() {   // 비동기적으로 작업하는 함수
    auto f1 = std::async([]() { do_work(3); }); // 비동기작업(1): 3초
    auto f2 = std::async([]() { do_work(3); }); // 비동기작업(2): 3초
    do_work(3); // 작업(3): 3초
    // 결국 세 작업이 동시에 진행되었으므로 총 3초가 걸림.

    f1.get();
    f2.get();
}

void do_work_sequential() { // 동기적으로 작업하는 함수(순차적)
    do_work(3); // 작업(1) 3초
    do_work(3); // 작업(2) 3초
    do_work(3); // 작업(3) 3초
    // 3초가 걸리는 작업을 3번 했으므로 총 9초.
}

int main() { 
    do_work_parallel();         // 3초
    // do_work_sequential();    // 9초
}