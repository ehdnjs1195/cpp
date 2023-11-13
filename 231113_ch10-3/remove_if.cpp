#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
/*
    template <typename Iter, typename Pred>
    remove_if(Iter first, Iter last, Pred pred) 

    Pred(predicate) 부분에 operator() 를 만들어 함수객체를 전달하거나, 실제 함수를 전달할 수도 있다.
*/
template <typename Iter>
void print(Iter begin, Iter end) {
    while(begin != end) {
        std::cout << "[" << *begin << "]" ;
        begin++;
    }
    std::cout << std::endl;
}
struct is_odd {
    bool operator()(const int& i) {return i % 2 == 1;}  // 홀수인지 확인하는 함수객체
};
// bool add(const int& i) {return i%2==1;} // 함수형태로도 전달 가능.

void ex1() {    // 홀수 원소 제거
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ----" << std::endl;
    print(vec.begin(), vec.end());

    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
    std::cout << "벡터에서 홀수 원소 제거 ----" << std::endl;
    print(vec.begin(), vec.end());
}

struct is_odd2{
    int num_delete;
    is_odd2() : num_delete(0) {}

    bool operator() (const int& i) {
        if(num_delete >= 2) return false;
        if(i%2==1) {
            num_delete++;
            return true;
        }    
        return false;
    }

};
void ex2() {    // 홀수인 원소 앞에 2개만 제거
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 ---" << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd2()), vec.end());
    print(vec.begin(), vec.end());
    /*
        결과를 보면 알 수 있지만, 3개가 삭제되었다.
        사실 C++ 표준에 따르면 remove_if 에 전달되는 함수 객체의 경우 이전의 호출에 의해 내부 상태가 달라지면 안됩니다. 
        => 인스턴스 변수 num_delete를 넣는것은 안된다.

    */
}

struct is_odd3 {    
  int* num_delete;  // 외부 변수로 받기위해 포인터로 정의하고

  is_odd3(int* num_delete) : num_delete(num_delete) {}  // 생성자 인자로 받기.

  bool operator()(const int& i) {
    if (*num_delete >= 2) return false;

    if (i % 2 == 1) {
      (*num_delete)++;
      return true;
    }

    return false;
  }
};
void ex3() {    //문제를 해결하기 위해 외부 변수로 빼서 받는 방법을 선택한다.
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 ---" << std::endl;
    int num_delete = 0; // 외부 변수로 선언.
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd3(&num_delete)), //주소 전달.
                vec.end());
    /*
        is_odd(&num_delete) 객체를 생성하여 remove_if에 전달하면 해당 객체의 operator() 함수가 호출되어 조건을 판단하게 됩니다.
    */
    print(vec.begin(), vec.end());
}
int main() {
    // ex1();
    // ex2();
    ex3();
}