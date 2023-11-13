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

// vec의 원소를 3으로 나눈 나머지가 2인 원소 찾기
int main() {
    std::vector<int> vec = {5,3,1,2,3,4};

    auto current = vec.begin();
    while(true) {
        current = std::find_if(current, vec.end(),[](int i) {return i % 3 == 2;});
        if(current == vec.end()) break;
        std::cout << "3으로 나눈 나머지가 2인 원소는 " << *current << std::endl;
        current++;
    }

}