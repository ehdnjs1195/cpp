#include <iostream>

class A{
    int *data;

public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void thrower() {
    // 예외를 발생시킴
    throw 1;
}

void do_something() {
    A *pa = new A();
    thrower();

    // 발생된 예외로 인해 delete pa가 호출되지 않는다! => 메모리 누수
    delete pa;
}

int main() {
    try{
        do_something();
    } catch(int i) {
        std::cout << "예외 발생!" << std::endl;
        // 예외 처리
    }
}
