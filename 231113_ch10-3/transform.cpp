#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
    while(begin != end) {
        std::cout << "[" << *begin << "] ";
        begin++;
    }
    std::cout << std::endl;
}
void ex1() {
    std::vector<int> vec = {5,3,1,2,3,4};

    std::cout << "처음 vec 상태 ----" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터 전체에 1을 더한다" << std::endl;
    std::transform(vec.begin(), vec.end(), vec.begin(), 
                                                    [](int i) {return i + 1;});
    print(vec.begin(), vec.end());
}
void ex2() {
    std::vector<int> vec = {5,3,1,2,3,4};
    std::vector<int> vec2(6, 0);    // 6칸을 0으로 초기화

    std::cout << "처음 vec과 vec2의 상태 -----" << std::endl;
    print(vec.begin(), vec.end());
    print(vec2.begin(), vec2.end());

    std::cout << "vec 전체에 1 더한 것을 vec2에 저장" << std::endl;
    std::transform(vec.begin(), vec.end(), vec2.begin(), [](int i) {return i+1;});
    print(vec.begin(), vec.end());
    print(vec2.begin(), vec2.end());

}
int main() {
    // ex1();
    ex2();
}