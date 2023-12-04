#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>
using std::string;
/*
    promise와 future를 이용해서 producer - consumer 구조를 만들 수 있다.
    아래 예제는 예외처리를 promise와 future로 구현한 예제이다.

    - future에 예외도 전달할 수 있음.
    - current_exception()함수는 exception_ptr를 반환한다.
    - 이를통해 비동기적 실행을 할 수 있고, 작업은 쓰레드를 통해 처리할 수 있다.
*/
void worker(std::promise<string>* p) {
    try {
        throw std::runtime_error("Some Error!");
    } catch (...) {
        // set_exception 에는 exception_ptr 를 전달해야 한다.
        p->set_exception(std::current_exception()); // make_exception_ptr()를 사용하는 것 보다 current_exception()이 더 간편함
    }
}
int main() {
    std::promise<string> p;

    // 미래에 string 데이터를 돌려 주겠다는 약속.
    std::future<string> data = p.get_future();

    std::thread t(worker, &p);

    // 미래에 약속된 데이터를 받을 때 까지 기다린다.
    data.wait();

    try {
        data.get();
    } catch (const std::exception& e) {
        std::cout << "예외 : " << e.what() << std::endl;
    }
    t.join();
}