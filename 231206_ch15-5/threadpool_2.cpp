#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace ThreadPool {
class ThreadPool {
 public:
  ThreadPool(size_t num_threads);
  ~ThreadPool();

  // job 을 추가한다.
  template <class F, class... Args>
  std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(
    F f, Args... args);

 private:
  // 총 Worker 쓰레드의 개수.
  size_t num_threads_;
  // Worker 쓰레드를 보관하는 벡터.
  std::vector<std::thread> worker_threads_;
  // 할일들을 보관하는 job 큐.
  std::queue<std::function<void()>> jobs_;
  // 위의 job 큐를 위한 cv 와 m.
  std::condition_variable cv_job_q_;
  std::mutex m_job_q_;

  // 모든 쓰레드 종료
  bool stop_all;

  // Worker 쓰레드
  void WorkerThread();
};

ThreadPool::ThreadPool(size_t num_threads)
    : num_threads_(num_threads), stop_all(false) {
  worker_threads_.reserve(num_threads_);
  for (size_t i = 0; i < num_threads_; ++i) {
    worker_threads_.emplace_back([this]() { this->WorkerThread(); });
  }
}

void ThreadPool::WorkerThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(m_job_q_);
    cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
    if (stop_all && this->jobs_.empty()) {
      return;
    }

    // 맨 앞의 job 을 뺀다.
    std::function<void()> job = std::move(jobs_.front());
    jobs_.pop();
    lock.unlock();

    // 해당 job 을 수행한다 :)
    job();
  }
}

ThreadPool::~ThreadPool() {
  stop_all = true;
  cv_job_q_.notify_all();

  for (auto& t : worker_threads_) {
    t.join();
  }
}

template <class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob(
  F f, Args... args) {
  if (stop_all) {
    throw std::runtime_error("ThreadPool 사용 중지됨");
  }

  using return_type = typename std::result_of<F(Args...)>::type;
  auto job =
    std::make_shared<std::packaged_task<return_type()>>(std::bind(f, args...)); // packaged_task는 결국 f함수의 리턴값을 갖는 future객체를 반환한다.
  std::future<return_type> job_result_future = job->get_future(); // 함수 f의 실행 결과 리턴값을 갖고 있는 future 객체이다.(이 경우는 work의 리턴타입이므로 int!!를 가진 future객체)
  {
    std::lock_guard<std::mutex> lock(m_job_q_);
    jobs_.push([job]() { (*job)(); });  // 람다함수에도 job의 복사본을 전달해서 job을 실행하는 시점에도 packaged_task 객체는 계속 살아있게 된다.
    /*
      <보충설명>
      ### (*job)()
      - std::packaged_task<return_type()> 타입의 스마트 포인터인 job를 역참조하고 함수 호출 연산자 ()를 사용하여 해당 std::packaged_task 객체를 실행하는 표현식이다.
      - std::packaged_task<return_type()>는 특정 타입의 작업을 나타내는 callable 객체를 감싸는데 사용됩니다. 
        여기서 return_type은 std::result_of<F(Args...)>::type로부터 추론되는 타입으로, 함수 F가 인자 Args...를 받아서 호출되었을 때의 반환 타입입니다.
      - 즉, std::packaged_task<return_type()>는 return_type 타입의 작업을 감싸고 있습니다. 
        이 작업은 ThreadPool::EnqueueJob 함수에서 받은 함수 F와 인자 Args...를 호출하여 얻은 결과를 나타냅니다.
      - 실제로 이 std::packaged_task 객체가 실행되는 시점은 ThreadPool의 worker 스레드에서 해당 작업이 큐에서 꺼내져서 실행될 때입니다. 
        따라서 (*job)()는 std::packaged_task 객체에 의해 감싸진 callable 객체를 호출하는 것이며, 이것은 ThreadPool에 의해 큐에서 꺼내진 작업을 실행하는 것과 동일합니다.
    */
  }
  cv_job_q_.notify_one();

  return job_result_future;
}

}  // namespace ThreadPool

int work(int t, int id) {
  printf("%d start \n", id);
  std::this_thread::sleep_for(std::chrono::seconds(t));
  printf("%d end after %ds\n", id, t);
  return t + id;
}

int main() {
  ThreadPool::ThreadPool pool(3);

  std::vector<std::future<int>> futures;
  for (int i = 0; i < 10; i++) {
    futures.emplace_back(pool.EnqueueJob(work, i % 3 + 1, i));
  }
  for (auto& f : futures) {
    printf("result : %d \n", f.get());
  }
}