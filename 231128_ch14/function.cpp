#include <iostream>
#include <functional>
#include <string>

int some_func1(const std::string& s) {
    std::cout << "Func1 호출! " << s << std::endl;
    return 0;
}
struct s {
    void operator()(char c) {std::cout << "Func2 호출! " << c << std::endl;}
};

int main() {
    std::function<int(const std::string&)> f1 = some_func1; // 1. 일반 함수
    std::function<void(char)> f2 = s(); // 2. Functor
    std::function<void()> f3 = [](){std::cout << "Func3 호출! "<< std::endl; }; // 3. 람다함수

    f1("hello~");
    f2('c');
    f3();
}