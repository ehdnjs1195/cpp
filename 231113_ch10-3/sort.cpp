#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

/*
    sort에 들어가는 반복자의 경우 반드시 임의접근 반복자(RandomAccessIterator) 타입을 만족해야 한다.
    (vector, deque 만 가능)

    # 리스트의 경우 양방향 반복자(BidirectionalIterator) 이므로 안된다.
*/
template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}
// sort 인자로 비교 조건을 전달할 수 있다.
struct int_compare {    
    bool operator() (const int& a, const int& b) const {return a > b;}  // 오름차순으로 정렬
};

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
    std::sort(vec.begin(), vec.end());
    
    std::cout << "오름차순 정렬 후 -----" << std::endl;
    print(vec.begin(), vec.end());
}
void ex2() {
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
    std::sort(vec.begin(), vec.end(), int_compare());
    
    std::cout << "내림차순 정렬 후 -----" << std::endl;
    print(vec.begin(), vec.end());
}
void ex3() {
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
    std::sort(vec.begin(), vec.end(), std::greater<int>());  // functional 해더에 이미 템플릿 클래스를 제공한다.
    // greater에 우리가 사용하고자 하는 타입을 넣게 되면 함수객체를 자동으로 만들어 준다.
    
    std::cout << "내림차순 정렬 후 -----" << std::endl;
    print(vec.begin(), vec.end());
}
int main() {
    // ex1();
    // ex2();
    ex3();
}