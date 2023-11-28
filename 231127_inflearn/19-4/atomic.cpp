#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>

// 레이스 컨디션: 같은 메모리 공간을 사용하기 때문에 발생하는 문제
/*
    병렬처리할 때 문제가 발생한다.
    원인) 작업 과정을 살펴보면
        1. cpu에서 shared_memory 값을 읽어오고
        2. cpu안에서 값을 더하고
        3. 다시 shared_memory를 보내서 값을 덮어 쓰기.
        => t1이 cpu로 읽어들인 사이에 t2가 이미 그 값을 바꾸었고, t1이 다시 값을 덮어 씌울 때가 발생함. 
        => 결론적으로 더하기 과정 하나가 사라진 것 처럼 되어버림.
    해결) 1. atomic : 위에 값을 더하는 일련의 과정을 하나로 묶어버림.
        2. mutex: lock기능으로 하나의 쓰레드만 접근하도록 함.
*/
using namespace std;

// 여러개의 쓰레드가 한개의 변수에 접근하도록 하는 예제
void ex1() {    // 1. atomic
    mutex mtx;
    atomic<int> shared_memory(0);  
    auto count_func = [&](){
        for(int i= 0; i < 1000; ++i) {
            this_thread::sleep_for(chrono::milliseconds(1));

            shared_memory++;    // atomic 클래스에 ++ 증감 연산자가 따로 오버로딩 되어있음!
            // shared_memory.fetch_add(1);  //atomic에서 쓰는 함수

        }
    };

    thread t1 = thread(count_func); // 1000번 더함
    thread t2 = thread(count_func); // 1000번 더함 => 그럼 2000이 나와야 하는데 안 나오는 경우가 발생함! 

    t1.join();
    t2.join();

    cout << "After" << endl;
    cout << shared_memory << endl;

}
void ex2() {    // 2. mutex lock / lock_guard
    mutex mtx;
    int shared_memory(0);
    auto count_func = [&](){
        for(int i= 0; i < 1000; ++i) {
            this_thread::sleep_for(chrono::milliseconds(1));
            // mtx.lock(); 
            std::lock_guard lock(mtx);  // lock이라는 변수를 현재 스코프 내에서 선언 하였고, 따로 언락이 필요 없음! 언락을 못할 경우를 대비할 수 있다.
            // 락가드는 권장사항임!!
            shared_memory++;  
            // mtx.unlock();   // 예외 처리하는 경우 unlock을 지나칠 수가 있음. 메모리 누수문제 등

        }
    };

    thread t1 = thread(count_func); // 1000번 더함
    thread t2 = thread(count_func); // 1000번 더함

    t1.join();
    t2.join();

    cout << "After" << endl;
    cout << shared_memory << endl;
}
void ex3() {    // 3. scoped_lock
    int shared_memory(0); 
    mutex mtx;
    auto count_func = [&](){
        for(int i= 0; i < 1000; ++i) {
            this_thread::sleep_for(chrono::milliseconds(1));

            // c++17부터 추가된 기능
            std::scoped_lock lock(mtx);  // 스코프 내에서(중괄호) 벗어나느 순간 자동으로 락이 풀림. 사용 권장됨!

            shared_memory++;    
        }
    };

    thread t1 = thread(count_func); // 1000번 더함
    thread t2 = thread(count_func); // 1000번 더함 

    t1.join();
    t2.join();

    cout << "After" << endl;
    cout << shared_memory << endl;

}
void ex4() {    // 4. 레이스 컨디션이 발생하는 경우는 언제지?
    mutex mtx;
    int shared_memory(0);  
    auto count_func = [&](){
        for(int i= 0; i < 1000; ++i) {
            // ex1에서 milliseconds를 뺌 => 그러면 놀랍게도 2000이 잘 나오는 것을 확인 할 수 있음.
            /*
                왜일까?
                1을 1000번 더하는 과정은 워낙 순식간이기 때문에 t1이 작업을 다 끝내고 난 뒤에 t2가 작업을 하게 된다.
                엄밀히 얘기하면 병렬 처리가 되지 않고, 순차적으로 실행된 셈이다.
                변수에 두 쓰레드가 동시에 접근하지 못한것일뿐!
                
                따라서 동시에 접근하게 되는 경우에는 레이스 컨디션이 발생할 수 있다. 
                이점을 항상 염두에 두고 작업해야 한다.
            */
            shared_memory++;    

        }
    };

    thread t1 = thread(count_func); // 1000번 더함
    thread t2 = thread(count_func); // 1000번 더함 

    t1.join();
    t2.join();

    cout << "After" << endl;
    cout << shared_memory << endl;

}
int main() {
    // ex1();
    // ex2();
    // ex3();
    ex4();
    return 0;
}