#include <iostream>
#include <thread>
#include <vector>
using std::thread;
using std::vector;

void worker(int& counter) {
    for(int i = 0; i < 10000; i++) {
        counter += 1;
    }
}

int main() {
    int counter = 0;

    vector<thread> workers;
    for(int i = 0; i < 4; i++) {
        // 레퍼런스로 전달하려면 ref 함수로 감싸야 한다. (지난 강좌 bind 함수 참조)
        workers.push_back(thread(worker, std::ref(counter)));
    }

    for (int i=0; i<4; i++) {
        workers[i].join();
    }
    
    std::cout << "Counter 최종 값: " << counter << std::endl;   // 정확하게 40000이 나와야 하지만, 이상한 값들이 나오게 된다. 
}