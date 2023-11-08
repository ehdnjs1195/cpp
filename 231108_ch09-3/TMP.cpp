#include <iostream>
/*
    TMP(Template Meta Programming)
    특징
    - c++ 모든 코드를 TMP로 변환할 수 있다. (코드량이 길어짐)
    장점
    - 컴파일 타임에 모든 연산이 끝나기 때문에 프로그램 실행 속도를 향상시킬 수 있다. (컴파일 시간이 늘어남)
    단점
    - 컴파일 타임에 연산하기 때문에 디버깅이 불가능.
    - c++ 컴파일러 특성 상 템플릿 오류시에 엄청난 길이의 오류를 발생
*/
// TMP 예제: 팩토리얼 구하기
//일반 함수 표현
int factorial(int n) {
    if(n == 1) return 1;
    return n * factorial(n-1);
}
template <int N>
struct Factorial {
    static const int result = N * Factorial<N-1>::result;
};
template <>
struct Factorial<1> {
    static const int result = 1;
};
void factorial_ex() {
    std::cout << "6! = 6*5*4*3*2*1 = " << Factorial<6>::result << std::endl;
}

// TMP 예제: 최대공약수 구하기
// 일반 함수표현
int gcd(int a, int b) {
    if (b==0) return a;
    return gcd(b, a % b);
}
template <int X, int Y>
struct GCD {
    static const int value = GCD<Y, X % Y>::value;
};
template <int X>
struct GCD<X, 0> {
    static const int value = X;
};
void gcd_ex() {
    std::cout << "gcd (36, 24) :: " << GCD<36, 24>::value << std::endl;
}

int main() {
    factorial_ex();
    gcd_ex();

}