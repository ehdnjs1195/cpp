#include <atomic>
#include <iostream>
#include <thread>
using std::thread;
std::atomic<bool> x(false);
std::atomic<bool> y(false);
std::atomic<int> z(0);

void write_x() { x.store(true, std::memory_order_release); }

void write_y() { y.store(true, std::memory_order_release); }

void read_x_then_y() {
  while (!x.load(std::memory_order_acquire)) {
  }
  if (y.load(std::memory_order_acquire)) {
    ++z;
  }
}

void read_y_then_x() {
  while (!y.load(std::memory_order_acquire)) {
  }
  if (x.load(std::memory_order_acquire)) {
    ++z;
  }
}
/*
    write_x()와 read_x_then_y() 동기화
    write_y()와 read_y_then_x() 동기화 되어있다.
    그렇다고 해서 read_x_then_y 와 read_y_then_x 두 쓰레드가 같은 순서로 x.store 와 y.store 를 관찰한다는 보장이 없습니다.
        - read_x_then_y 의 입장에서는 x.store 가 y.store 보다 먼저 발생해도 되고, 
        - read_y_then_x 입장에서는 y.store 가 x.store 보다 먼저 발생해도 된다는 것입니다.
    따라서 if문 안의 load가 false가 되면서 z는 0이 될 수도 있다.
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