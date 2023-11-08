#include <iostream>

// TMP를 이용하여 유리수를 표현하는 Ratio 클래스 만들기
template <int N, int D =1>
struct Ratio {
    typedef Ratio<N, D> type;
    static const int num = N;
    static const int den = D;
};
template <class R1, class R2>
struct _Ratio_add {
    typedef Ratio<R1::num * R2::den + R1::den*R2::num, R1::den*R2::den> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1,R2>::type {};   // _Ratio_add 를 상속받아 _Ratio_add의 기능을 사용. => 바로 type

int main() {
    typedef Ratio<5, 3> rat;
    typedef Ratio<1, 6> rat2;
    typedef Ratio_add<rat, rat2> rat3;

    std::cout << rat3::num << " / " << rat3::den << std::endl;
}