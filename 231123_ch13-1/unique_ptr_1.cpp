#include <iostream>
#include <memory>

class A {
  int *data;

 public:
    A() {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
    }

    void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void do_something() {
    std::unique_ptr<A> pa(new A());
    pa->some(); // unique_ptr는 '->'연산자를 오버로딩 했기 때문에 포인터처럼 사용할 수 있다.
}

int main() { do_something(); }  // do_something() 함수가 종료될 때 pa는 스택에 정의된 객체이기 때문에 자동으로 소멸자가 호출된다. => unique_ptr 덕분에 메모리 관리를 할 수 있다.