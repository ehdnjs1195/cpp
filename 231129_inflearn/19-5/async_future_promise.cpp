#include <iostream>
#include <future>   // async, future, promise
#include <thread>

using namespace std;

void multi_threading(){
    // multi-threading
    {
        int result;
        std::thread t([&]{result = 1 + 2;});
        t.join();   // 쓰레드가 일을 마칠 때까지 기다림
        cout << result << endl;
    }

}
void task_based_parallelism(){
    // task-based parallelism   => 위의 멀티쓰레딩보다 더 선호된다.
    {
        // std::future<int> fut = ...
        auto fut = std::async([] {return 1 + 2;});  // 비동기적인 async
        // main thread와 별도로 async하게 즉, 비동기적으로 작업을 수행한다.
        /*
            multi-threading & task-based parallelism 차이
            1. multi-threading: 쓰레드의 관리, 어떤 일을할지 지정하는 것이 중점
            2. task-based parallelism: 어떤일을 할지가 중점.
                => return 해주는 값을 현재 받을 수 있는 것이 아님. 오랜 시간이 걸린 작업이라면 return 값을 바로 받을 수 있다는 보장이 없음.
        */
        cout << fut.get() << endl;  // async가 작업을 마칠 때까지 기다렸다가 int 로 return 값을 받게된다. 
    }
}
void future_and_promise(){
    // future and promise
    {
        std::promise<int> prom;
        auto fut = prom.get_future();

        auto t = std::thread([](std::promise<int>&& prom)
        {
            prom.set_value(1 + 2);  // prom이 값을 받을 때까지 
        }, std::move(prom));
        
        cout << fut.get() << endl;  // fut.get이 기다림.    약속(promise)이 완수 되기를 미래(future)가 기다리는 형태.
        t.join();
    }
}
void diff_thread_and_async() {  // 쓰레드와 비동기의 중요한 차이점.
    auto f1 = std::async([] {
        cout << "async1 start" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "async1 end" << endl;
    });

    auto f2 = std::async([] {   
        cout << "async2 start" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "async2 end" << endl;
    });

    cout << "Main function" << endl;
    /*
        1. 비동기는 join을 하지 않아도 문제가 생기지 않는다.
          따라서, 옵티마이제이션을 할 때 두 차이를 숙지해야 함.
        
            Main function
            async1 start
            async2 start
            async2 end
            async1 end    
        와 같이 결과가 출력된다. 왜일까? mainfunction과 별도로 비동기적으로 실행되기 때문.
        
        - async를 thread로 바꿔서 실행해보자. 
          join이 없기 때문에 mainthread가 먼저 끝나버리게 되고 따라서 문제가 발생함.(join을 써주면 정상작동)
    */
}
void diff_thread_and_async2() {  // 쓰레드와 비동기의 중요한 차이점.
    std::async([] {
        cout << "async1 start" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        cout << "async1 end" << endl;
    });

    std::async([] {   
        cout << "async2 start" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "async2 end" << endl;
    });

    cout << "Main function" << endl;
    /*
        2. future를 없앤 상황에서(auto로 받는 타입 삭제) 실행해보면

        => async가 future와 연결이 되어있지 않을 경우에는
           그냥 sequensing 인 것 처럼 처리된다. 순차적으로 async1 -> async2 -> main 실행
    */

}
int main() {
    // multi_threading();
    // task_based_parallelism();
    // future_and_promise();
    // diff_thread_and_async();
    diff_thread_and_async2();

    return 0;
}