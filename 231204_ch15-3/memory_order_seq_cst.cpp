#include <atomic>
#include <iostream>
#include <thread>
using std::memory_order_seq_cst;
using std::thread;

std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void write_x() { x.store(true, memory_order_seq_cst); }

void write_y() { y.store(true, memory_order_seq_cst); }

void read_x_then_y() {
    while (!x.load(memory_order_seq_cst)) {
    }
    if (y.load(memory_order_seq_cst)) {
        ++z;
    }
}

void read_y_then_x() {
    while (!y.load(memory_order_seq_cst)) {
    }
    if (x.load(memory_order_seq_cst)) {
        ++z;
    }
}
/*
    memory_order_seq_cst 를 사용하게 된다면, 해당 명령을 사용하는 메모리 연산들 끼리는 모든 쓰레드에서 동일한 연산 순서를 관찰할 수 있도록 보장해줍니다. 
    => 한마디로 내가 짠 순서대로 될 수 있도록 보장해준다.
    따라서, z는 0이 나올 수 없게된다.

    하지만, memory_order_seq_cst 는 일부 계열(ARM) CPU에서 동기화 비용이 매우 크다. 따라서 정말 필요할 때만 사용해야 한다.
*/
int main() {
    thread a(write_x);
    thread b(write_y);
    thread c(read_x_then_y);
    thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    std::cout << "z : " << z << std::endl;
}