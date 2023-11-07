#include <iostream>
#include <typeinfo>

template <int N>
struct Int {
    static const int num = N;
};

template <typename T, typename U>
struct add {
    typedef Int<T::num + U::num> result;
};

int main() {
    // one과 two는 객체가 아닌 타입이다. 각각 
    typedef Int<1> one; //Int<1> 타입
    one::num;   // 1
    typedef Int<2> two; //Int<2> 타입
    /*
        <의미 파악하기!>

        이제 one과 two는 특정화된 정수 상수를 가지고 있는 '타입' 이므로! 컴파일 시간에(프로그램이 실행되기 전! => 변수에 마우스를 올려보면 컴파일 시간에 값이 보이는 것을 알 수 있다.) 
        '1'과 '2'라는 값으로 특정화된 정수 상수를 가지고 사용할 수 있게 되는 것이다.

    */
    typedef add<one, two>::result three;    //Int<3> 타입
    /*
        typedef add<one, two>::result은 Int<1+2>로 Int<3> 타입의 'result'로 정의하는 것이고, 이를 three로 별칭을 부여하는 것이다.
        최종적으로 => typedef Int<3> three; 가 되는 것이다. 따라서 three타입이 갖는 num은 3이다.
    */

    std::cout << "Addtion result : " << three::num << std::endl;
}