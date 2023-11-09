#include <iostream>
#include <typeinfo>

int sum(int a, int b){ return a + b;}

class SomeClass {
    int data;

    public:
    SomeClass(int d) : data(d){}
    SomeClass(const SomeClass& s) : data(s.data) {}
};

int main() {
    auto c = sum(1,2);
    auto num = 1.0 + 2.0;

    SomeClass some(10);
    auto some2 = some;

    auto some3(10); // SomeClass 객체를 만들까?

    std::cout << "c의 타입은? :: " << typeid(c).name() << std::endl;    // int -> i
    std::cout << "num 의 타입은? :: " << typeid(num).name() << std::endl;   // double -> d
    std::cout << "some2의 타입은? :: " << typeid(some2).name() << std::endl;// some 타입으로 부터 복사되므로 SomeClass 타입임
    std::cout << "some3의 타입은? :: " << typeid(some3).name() << std::endl;// SomeClass 타입이 아닌 그저 int타입 변수로 만들어 버린다.
}