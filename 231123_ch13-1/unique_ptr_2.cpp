#include <iostream>


class A {
    public:
    A(int a){};
    A(const A& a) = delete; // 명시적으로 복사 생성자를 사용하지 못하도록 표현함.
    // => unique_ptr도 복사 생성자가 명시적으로 삭제되었다.
    // 만약 특정 객체를 여러개의 unique_ptr들이 소유한다면, 소멸될 때 전체를 delete하려 해서 double free 버그가 발생하게 되기 때문이다.
};

int main() {
    A a(3);  // 가능
    // A b(a);  // 불가능 (복사 생성자는 삭제됨)
}