#include <iostream>

// TMP를 이용하여 유리수를 표현하는 Ratio 클래스 만들기
/*
    C++11 부터 typedef 대신 using이라는 키워드를 사용할 수 있다.
    <수정> gcd(최대공약수) 를 이용하여 기약분수로 만드는 과정 추가
*/
template <int X, int Y>
struct GCD {    // 최대공약수 구하는 템플릿 클래스
    static const int value = GCD<Y, X % Y>::value;
};
template <int X>
struct GCD<X,0> {
    static const int value = X;
};
// 기약분수를 나타내는 템플릿 함수
template <int N, int D =1>
struct Ratio {  
private:
    static const int gcd_ = GCD<N, D>::value;
public:
    using type = Ratio<N/gcd_, D/gcd_>;
    static const int num = N/gcd_;
    static const int den = D/gcd_;
};
// 분수의 합
template <class R1, class R2>
struct _Ratio_add { 
    using type = Ratio<R1::num * R2::den + R1::den*R2::num, R1::den*R2::den>;
};
template <class R1, class R2>   // _Ratio_add 를 상속받았기 때문에 _Ratio_add의 기능을 사용 => 일일히 _Ratio_add<R1,R2>::type 을 써줄 필요가 없음
struct Ratio_add : _Ratio_add<R1,R2>::type {};   
//분수의 차
template <class R1, class R2>
struct _Ratio_subtract {   
    using type = Ratio<R1::num*R2::den - R2::num*R2::den, R1::den*R2::den>;
};
template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};
//분수의 곱
template <class R1, class R2>
struct _Ratio_multiply {
    using type = Ratio<R1::num * R2::num, R1::den * R2::den>;
};
template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};
//분수의 나눗셈
template <class R1, class R2>
struct _Ratio_divide {
    using type = Ratio<R1::num * R2::den, R1::den * R2::num>;
};
template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

int main() {
    using r1 = Ratio<5, 3>;
    using r2 = Ratio<2, 12>;

    using r3 = Ratio_multiply<r1, r2>; 
    typedef _Ratio_multiply<r1, r2>::type r4;   // r3와 같은 표현
    std::cout << "5/3 * 2/12 = " << r3::num << "/" << r3::den << " : " << r4::num << "/" << r4::den << std::endl;

    _Ratio_divide<r1, r2>::type::num;
}