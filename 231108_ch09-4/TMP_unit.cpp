#include <iostream>


template <int X, int Y>
struct GCD {
  static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0> {
  static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
 private:
  const static int _gcd = GCD<N, D>::value;

 public:
  typedef Ratio<N / _gcd, D / _gcd> type;
  static const int num = N / _gcd;
  static const int den = D / _gcd;
};
template <class R1, class R2>
struct _Ratio_add {
  using type = Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_subtract {
  using type = Ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_multiply {
  using type = Ratio<R1::num * R2::num, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_divide {
  using type = Ratio<R1::num * R2::den, R1::den * R2::num>;
};

template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

template <typename U, typename V, typename W>
struct Dim {
  using M = U;  // kg
  using L = V;  // m
  using T = W;  // s

  using type = Dim<M, L, T>;
};

template <typename U, typename V>
struct add_dim_ {
  typedef Dim<typename Ratio_add<typename U::M, typename V::M>::type,   // kg
              typename Ratio_add<typename U::L, typename V::L>::type,   // m
              typename Ratio_add<typename U::T, typename V::T>::type>   // s
      type;
};

template <typename U, typename V>
struct subtract_dim_ {
  typedef Dim<typename Ratio_subtract<typename U::M, typename V::M>::type,
              typename Ratio_subtract<typename U::L, typename V::L>::type,
              typename Ratio_subtract<typename U::T, typename V::T>::type>
      type;
};

template <typename T, typename D>   // T는 객체의 유형(타입), D는 차원.
struct quantity {
    T q;
    using dim_type = D;

    quantity operator+(quantity<T, D> quant) {
        return quantity<T, D>(q + quant.q); // 기존의 q에 입력받은 quant객체의 q를 더하여 새로운 quantity 객체를 반환하여 준다.
    }

    quantity operator-(quantity<T, D> quant) {
        return quantity<T, D>(q - quant.q);
    }

    // 곱셈과 나눗셈은 Dim이 일치하지 않아도 되며, 새로운 차원의 데이터가 나온다.
    template <typename D2>
    quantity<T, typename add_dim_<D, D2>::type> operator*(quantity<T, D2> quant) {
        return quantity<T, typename add_dim_<D, D2>::type>(q * quant.q);
    }

    template <typename D2>
    quantity<T, typename subtract_dim_<D, D2>::type> operator/(quantity<T, D2> quant) {
        return quantity<T, typename subtract_dim_<D, D2>::type>(q / quant.q);
    }
    quantity<T, D> operator*(T scalar) { return quantity<T, D>(q * scalar); }
    quantity<T, D> operator/(T scalar) { return quantity<T, D>(q / scalar); }

    quantity(T q) : q(q) {}
};

// quantity를 ostream으로 출력해주는 함수 ( << 를 통해서) 
template <typename T, typename D>
std::ostream& operator<<(std::ostream& out, const quantity<T, D>& q) {
    out << q.q << "kg^" << D::M::num / D::M::den << "m^" << D::L::num / D::L::den
        << "s^" << D::T::num / D::T::den;

    return out;
}

void ex1() {
    using one = Ratio<1, 1>;
    using zero = Ratio<0, 1>;

    // 각각의 단위들이 서로 다른 타입이므로 서로 +, - 연산이 불가능하다. 각 타입마다 operator가 각각 정의되기 때문에.
    quantity<double, Dim<one, zero, zero>> kg(1);   // double type의 1로 생성자에서 초기화하며 객체 생성. => 모양을 보고 헷갈리지 말아야 한다. 이는 단순히 객체를 생성한 것과 마찬가지이므로
    quantity<double, Dim<zero, one, zero>> meter(1);    // ex) double kg(1); 과 같은 형태라고 보면 된다.
    quantity<double, Dim<zero, zero, one>> second(1);
    
    auto F = kg * meter / (second * second);    // F의 타입은 오른쪽 계산을 통해 추론할 수 있기 때문에 auto로 적어주어도 컴파일러가 잘 받아온다.
    // Good
    kg + kg;

    // Bad
//   kg + meter;
}
void ex2() {
    using one = Ratio<1, 1>;
    using zero = Ratio<0, 1>;

    quantity<double, Dim<one, zero, zero>> kg(2);
    quantity<double, Dim<zero, one, zero>> meter(3);
    quantity<double, Dim<zero, zero, one>> second(1);

    // F 의 타입은 굳이 알필요 없다!
    auto F = kg * meter / (second * second);
    std::cout << "2 kg 물체를 3m/s^2 의 가속도로 밀기 위한 힘의 크기는? " << F
                << std::endl;
}

int main() {
//    ex1();
   ex2();
}