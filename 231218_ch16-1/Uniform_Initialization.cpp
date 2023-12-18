#include <iostream>

class A
{
public:
    A() { std::cout << "A 의 생성자 호출!" << std::endl; }
};

class B
{
public:
    B(int x, double y) { std::cout << "A 생성자 호출" << std::endl; }
};

// 중괄호를 이용해서 생성자를 호출하는 경우는 암시적 타입 변환들이 불가능하다.
B func()
{
    return {1, 2.3}; // B(1, 2.3) 과 동일. 리턴시에 굳이 타입을 적어주지 않아도 된다.
}

int main()
{
    A a{}; // 균일한 초기화!
    func();
}