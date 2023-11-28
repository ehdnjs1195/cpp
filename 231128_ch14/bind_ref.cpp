#include <functional>
#include <iostream>

struct S {
    int data;
    S(int data) : data(data) { std::cout << "일반 생성자 호출!" << std::endl; }
    S(const S& s) {
        std::cout << "복사 생성자 호출!" << std::endl;
        data = s.data;
    }

    S(S&& s) {
        std::cout << "이동 생성자 호출!" << std::endl;
        data = s.data;
    }
};

void do_something(S& s1, const S& s2) { s1.data = s2.data + 3; }

void wrong_code() {
    S s1(1), s2(2);

    std::cout << "Before : " << s1.data << std::endl;

    // s1 이 그대로 전달된 것이 아니라 s1 의 복사본이 전달됨! => 따라서 do_something() 함수 이후에 값이 반영되지 않는다.
    auto do_something_with_s1 = std::bind(do_something, s1, std::placeholders::_1);
    do_something_with_s1(s2);

    std::cout << "After :: " << s1.data << std::endl;
}
void right_code() {
    S s1(1), s2(2);

    std::cout << "Before : " << s1.data << std::endl;

    //ref 함수는 전달받은 인자를 복사 가능한 레퍼런스로 변환해준다. 따라서 bind 함수 안으로 레퍼런스가 잘 전달된다.
    auto do_something_with_s1 = std::bind(do_something, std::ref(s1), std::placeholders::_1);
    // 참고로 const 레퍼런스의 경우 cref 함수를 호출하면 된다.
    do_something_with_s1(s2);

    std::cout << "After :: " << s1.data << std::endl;
    }
int main() {
    // wrong_code();
    right_code();
}