#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

template <typename Iter>
void print(Iter begin, Iter end) {
    while(begin != end) {
        std::cout << "[" << *begin << "] ";
        begin++;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 -----" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 값이 3인 원소 제거 ---" << std::endl;
    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
    /*
        std::remove(begin, end, 원소) => 찾은 원소를 뒤로 밀고 그 원소의 위치 반복자를 반환한다.
        따라서, 실제 원소를 삭제하는 것이 아니라 자리만 바뀌는 것. 
        erase 함수를 호출하여 실제로 원소를 지워주어야 한다.
    */
    print(vec.begin(), vec.end());
}