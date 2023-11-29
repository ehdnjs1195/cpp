#include <iostream>
#include <mutex>  // mutex 를 사용하기 위해 필요
#include <thread>
/*
  실행해보면 어디서 데드락되었는지 확인할 수 있다.
*/
void worker1(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10000; i++) {
    std::lock_guard<std::mutex> lock1(m1);
    if(!m1.try_lock()) std::cout << "worker1 m1 이미 lock 되었음" << std::endl;
    std::lock_guard<std::mutex> lock2(m2);
    if(!m2.try_lock()) std::cout << "worker1 m2 이미 lock 되었음" << std::endl;

    // Do something
    std::cout << "worker1: " << i << std::endl;
  }
}

void worker2(std::mutex& m1, std::mutex& m2) {
  for (int i = 0; i < 10000; i++) {
    std::lock_guard<std::mutex> lock2(m2);
    if(!m2.try_lock()) std::cout << "worker2 m2 이미 lock 되었음" << std::endl;
    std::lock_guard<std::mutex> lock1(m1);
    if(!m1.try_lock()) std::cout << "worker2 m1 이미 lock 되었음" << std::endl;

    // Do something
    std::cout << "worker2: " << i << std::endl;

  }
}

int main() {
  int counter = 0;
  std::mutex m1, m2;  // 우리의 mutex 객체

  std::thread t1(worker1, std::ref(m1), std::ref(m2));
  std::thread t2(worker2, std::ref(m1), std::ref(m2));

  t1.join();
  t2.join();

  std::cout << "끝!" << std::endl;
}