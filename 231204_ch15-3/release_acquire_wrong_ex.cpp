#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
using std::memory_order_relaxed;

void producer(std::atomic<bool>* is_ready, int* data) {
  *data = 10;
  is_ready->store(true, memory_order_relaxed);
  // relaxed이기 때문에 *data = 10;이 store보다 뒤에 올 수 있다.
}

void consumer(std::atomic<bool>* is_ready, int* data) {
  // data 가 준비될 때 까지 기다린다.
  while (!is_ready->load(memory_order_relaxed)) {
  }
  // relaxed이기 때문에 cout이 먼저될 수 있다.
  std::cout << "Data : " << *data << std::endl;
}

// relaxed는 순서 재배치가 가능하기 때문에 store 되기 전에 load가 되거나 load가 되기전에 store가 될 수 있다. 따라서 data가 0이 나올 수 있는 것이다.

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