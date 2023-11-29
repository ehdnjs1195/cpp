#include <iostream>
#include <mutex>  // mutex 를 사용하기 위해 필요
#include <thread>

/*
    deadlock을 방지하는 방법
        1. starvation
        2. 중첩된 lock 을 사용하는 것을 피해라
        3. Lock을 소유하고 있을 때 유저 코드를 호출하는 것을 피해라
        4. Lock들을 언제나 정해진 순서로 획득해라
    
*/
void worker1(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 100; i++) {
        m1.lock();
        m2.lock();
        std::cout << "Worker1 Hi! " << i << std::endl;

        m2.unlock();
        m1.unlock();
    }
}

void worker2(std::mutex& m1, std::mutex& m2) {
    for (int i = 0; i < 100; i++) {
        while (true) {
            m2.lock();

            // m1 이 이미 lock 되어 있다면 "야 차 빼" 를 수행하게 된다. 
            if (!m1.try_lock()) {   // lock을 할 수 있다면, lock을 하고 true 리턴, lock을 못하면 그냥 false 리턴
                m2.unlock();
                continue;
            }

            std::cout << "Worker2 Hi! " << i << std::endl;
            m1.unlock();
            m2.unlock();
            break;
        }
    }
}

int main() {
  std::mutex m1, m2;  // 우리의 mutex 객체

  std::thread t1(worker1, std::ref(m1), std::ref(m2));
  std::thread t2(worker2, std::ref(m1), std::ref(m2));

  t1.join();
  t2.join();

  std::cout << "끝!" << std::endl;
}