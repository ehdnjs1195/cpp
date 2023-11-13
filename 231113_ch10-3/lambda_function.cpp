#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << "[" << *begin << "]";
        begin++;
    }
    std::cout << std::endl;
}

void ex1() { // 람다함수 사용
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                                                    [](int i) -> bool { return i % 2 == 1; }),
                                                    vec.end());
    print(vec.begin(), vec.end());
}
void ex2() {    // capture list 를 이용해 함수 외부의 변수 사용.
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 ---" << std::endl;
    int num_erased = 0;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                        [&num_erased](int i) {
                            if (num_erased >= 2)
                            return false;
                            else if (i % 2 == 1) {
                            num_erased++;
                            return true;
                            }
                            return false;
                        }),
                vec.end());
    print(vec.begin(), vec.end());
}

class SomeClass {
std::vector<int> vec;

int num_erased;

public:
SomeClass() {
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    num_erased = 0;
/*
    this로 복사본을 전달받는다. (참고로 this는 레퍼런스로 전달할 수 없다.)
*/
vec.erase(std::remove_if(vec.begin(), vec.end(),
                        [this](int i) { 
                        if (this->num_erased >= 2)
                            return false;
                        else if (i % 2 == 1) {
                            this->num_erased++;
                            return true;
                        }
                        return false;
                        }),
        vec.end());
}
};

int main() {
    // ex1();
    ex2();
}