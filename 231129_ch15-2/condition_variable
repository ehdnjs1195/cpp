#include <chrono>              // std::chrono::miliseconds
#include <condition_variable>  // std::condition_variable
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

void producer(std::queue<std::string>* downloaded_pages, std::mutex* m,
              int index, std::condition_variable* cv) {
  for (int i = 0; i < 5; i++) {
    // 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
    // 각 쓰레드 별로 다운로드 하는데 걸리는 시간이 다르다.
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
    std::string content = "웹사이트 : " + std::to_string(i) + " from thread(" +
                          std::to_string(index) + ")\n";

    // data 는 쓰레드 사이에서 공유되므로 critical section 에 넣어야 한다.
    m->lock();
    downloaded_pages->push(content);
    m->unlock();

    // consumer 에게 content 가 준비되었음을 알린다.
    cv->notify_one();
  }
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m,
              int* num_processed, std::condition_variable* cv) {
  while (*num_processed < 25) {
    std::unique_lock<std::mutex> lk(*m);  // 객체가 생성될 때에 뮤텍스를 lock 

    cv->wait( //lk 를 unlock 한 뒤에, 누군가 깨워주기 전까지 영원히 sleep
        lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });
    // 깨어나면 다시 mutext를 lock함

    if (*num_processed == 25) {
      lk.unlock();
      return;
    }

    // 맨 앞의 페이지를 읽고 대기 목록에서 제거한다.
    std::string content = downloaded_pages->front();
    downloaded_pages->pop();

    (*num_processed)++;
    lk.unlock();

    // content 를 처리한다.
    std::cout << content;
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
  }
}

int main() {
  // 현재 다운로드한 페이지들 리스트로, 아직 처리되지 않은 것들이다.
  std::queue<std::string> downloaded_pages;
  std::mutex m;
  std::condition_variable cv;

  std::vector<std::thread> producers;
  for (int i = 0; i < 5; i++) {
    producers.push_back(
        std::thread(producer, &downloaded_pages, &m, i + 1, &cv));
  }

  int num_processed = 0;
  std::vector<std::thread> consumers;
  for (int i = 0; i < 3; i++) {
    consumers.push_back(
        std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
  }

  for (int i = 0; i < 5; i++) {
    producers[i].join();
  }

  // 나머지 자고 있는 쓰레드들을 모두 깨운다.
  cv.notify_all();    // cv.notify_all() 을 하지 않는다면, 자고 있는 consumer 쓰레드들의 경우 join 되지 않는 문제가 발생

  for (int i = 0; i < 3; i++) {
    consumers[i].join();
  }
}