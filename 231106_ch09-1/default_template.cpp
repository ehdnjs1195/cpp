#include <iostream>
#include <string>

template <typename T, int num = 5>  // = 5는 디폴트 인자.
T add_num(T t) {
    return t + num;
}
void ex1() {
    int x=3;
    std::cout << "x : " << add_num(x) << std::endl;
    // add_num<int, 5> 를 한 것과 동일함. int 는 컴파일러가 자동으로 추론해줌.
}

template <typename T, typename Comp>
T Min(T a, T b) {   // 두 타입을 비교하여 작은 것을 리턴하는 함수
    Comp comp;
    if(comp(a, b)) {
        return a;
    }
    return b;
}

template <typename T>
struct Compare {
    bool operator()(const T& a, const T& b) const {return a < b;}
};
void ex2() {
    int a = 3, b = 4;
    std::cout << "min : " << Min<int, Compare<int>>(a, b);
    // => Compare 타입을 굳이 써서 전달해야 함
}

// 하지만 디폴트 템플릿 인자를 사용하면 아래와 같이 매우 간단하게 사용할 수 있다.
template <typename T, typename Comp = Compare<T>>   // 디폴트 사용
T Min2(T a, T b) {
    Comp comp;
    if(comp(a, b)) {
        return a;
    }
    return b;
}
void ex3() {
    int a=3, b=5;
    std::cout << "Min " << a << " , " << b << " :: " << Min2(a, b) << std::endl;

    std::string s1 = "abc", s2 = "def";
    std::cout << "Min " << s1 << " , " << s2 << " :: " << Min2(s1, s2) << std::endl;
}
int main()
{
    // ex1();
    ex3();
}