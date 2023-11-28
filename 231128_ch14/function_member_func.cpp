#include <functional>
#include <iostream>
#include <string>

class A {
    int c;

    public:
    A(int c) : c(c) {}
    int some_func() {
        std::cout << "비상수 함수: " << ++c << std::endl;
        return c;
    }

    int some_const_function() const {
        std::cout << "상수 함수: " << c << std::endl;
        return c;
    }

    static void st() {}
};

int main() {
    A a(5);
    // std::function<int()> f1 = a.some_func;   // 함수의 입장에서 자신을 호출하는 객체가 무엇인지 모름. 따라서 어떤 객체인지를 전달해주어야 함.
    std::function<int(A&)> f1 = &A::some_func;  // A클래스의 some_func 함수 객체를 만들겠다.
    std::function<int(const A&)> f2 = &A::some_const_function;  // A클래스의 some_const_function 함수 객체를 만들겠다.

    f1(a);  // 객체 a를 전달함으로 같은 객체 내의 멤버 함수를 호출하는 형태의 꼴이 된다.
    f1(a);
    f2(a);
}