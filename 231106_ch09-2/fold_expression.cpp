#include <iostream>

template <typename... Ints>
int sum_all(Ints... nums) {
    return (... + nums);
}
void ex1() {
    // 1 + 4 + 2 + 3 + 10
    std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
    // return ((((1 + 4) + 2) + 3) + 10); 단항 좌측 Fold
}

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums) {
    return (start - ... - nums);
}
void ex2() {
    std::cout << diff_from(100, 1, 4, 2, 3, 10) << std::endl;
}

// , 연산자를 이용하면 각각의 인자들에 대해 원하는 식을 실행할 수 있다.
class A {
public:
    void do_something(int x) const {    //const 함수 내에서는 const가 붙은 다른 함수를 제외한 일반 함수는 호출하지 못한다.
        std::cout << "Do something with " << x << std::endl;
    }
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums) {
    // 각각의 인자들에 대해 do_something 함수들을 호출한다.
    (t.do_something(nums), ...);
}

int main() {
    // ex1();
    // ex2();
    A a;
    do_many_things(a, 1, 3, 2, 4);
}