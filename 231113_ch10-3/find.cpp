#include <algorithm>
#include <iostream>
#include <functional>
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

void ex1() {    // vec에서 3의 위치 찾기
    std::vector<int> vec = {5,3,1,2,3,4};

    auto result = std::find(vec.begin(), vec.end(), 3); //vec에서 3을 찾아 처음으로 가리키는 반복자 반환
    std::cout << "vec 원소중 3의 위치는 " << std::distance(vec.begin(), result) + 1 << std::endl; 
    // std::distance 함수는 두 반복자 사이의 요소 개수를 계산하여 반환하는 함수
}
void ex2() {    // vec에서 3의 위치를 모두 찾기
    std::vector<int> vec = {5,3,1,2,3,4};

    auto current = vec.begin();
    while(true) {
        current = std::find(current, vec.end(), 3);
        if(current == vec.end()) break;
        std::cout << "3은 " << std::distance(vec.begin(), current) +1 << "번째 원소이다." << std::endl;
        current++;
    }
}

int main() {
    // ex1();
    ex2();
}