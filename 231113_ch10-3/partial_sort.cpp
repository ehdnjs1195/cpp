#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
/*
    std::partial_sort(start, middle, end) 로 3개의 인자를 기본으로 받는다.
    전체 start-end 원소중에 start-middle 원소들을 작은순으로 정렬한다.
*/
template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}

void ex1() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(2);

    std::cout << "정렬 전 -----" << std::endl;
    print(vec.begin(), vec.end());
    std::partial_sort(vec.begin(), vec.begin()+3, vec.end());  
    
    std::cout << "정렬 후 -----" << std::endl;
    print(vec.begin(), vec.end());
}

int main() {
    ex1();
}