#include <future>
#include <iostream>
#include <thread>

int some_task(int x) { return 10 + x; }

int main() {
    // int(int) : int 를 리턴하고 인자로 int 를 받는 함수. (std::function 참조)
    std::packaged_task<int(int)> task(some_task);
    /*
        packaged_task는 비동기적 함수(Callable)을 인자로 받는다.
        - 함수를 실행하여 그 함수의 리턴값을 promise에 설정한다.
        - 그 뒤에 마찬가지로 future의 get 함수로 데이터를 받을 수 있다.

        참고로, packaged_task와 promise는 복사생성이 불가능하기 때문에 명시적으로 move해줘야 한다.
    */
    std::future<int> start = task.get_future();

    std::thread t(std::move(task), 5);

    std::cout << "결과값 : " << start.get() << std::endl;
    t.join();
}