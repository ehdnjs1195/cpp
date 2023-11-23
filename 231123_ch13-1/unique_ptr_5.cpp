#include <iostream>
#include <memory>

class Foo {
    int a, b;

public:
    Foo(int a, int b) : a(a), b(b) { std::cout << "생성자 호출!" << std::endl; }
    void print() { std::cout << "a : " << a << ", b : " << b << std::endl; }
    ~Foo() { std::cout << "소멸자 호출!" << std::endl; }
};

int main() {
    // make_unique 함수는 아예 템플릿 인자로 전달된 클래스의 생성자에 인자들에 직접 완벽한 전달을 수행합니다.
    // std::unique_ptr<Foo> ptr(new Foo(3, 5)); 할 필요가 없음.
    auto ptr = std::make_unique<Foo>(3, 5);
    ptr->print();
}