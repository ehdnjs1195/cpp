#include <functional>
#include <iostream>

void add(int x, int y) {
    std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
    std::cout << x << " - " << y << " = " << x - y << std::endl;
}
int main() {
    auto add_with_2 = std::bind(add, 2, std::placeholders::_1); // 첫번재 인자는 2로 고정이고 두번째 인자를 받겠다.
    add_with_2(3);

    // 두 번째 인자는 무시된다.
    add_with_2(3, 4);

    auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);   // 첫번째 인자를 받겠다. 두번째 인자는 2로 고정.
    auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);    // 함수를 쓸 때 첫번째 자리에 두번째(_2) 인자를, 두번째 자리에 첫번째(_1) 인자를 넣겠다.

    subtract_from_2(3);  // 3 - 2 를 계산한다.
    negate(4, 2);        // 2 - 4 를 계산한다
}