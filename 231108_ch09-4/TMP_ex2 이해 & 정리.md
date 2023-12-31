# TMP로 소수를 판별하는 프로그램 만들기

## 문제1. 템플릿 부분 특수화 시에는 반드시 다른 연산자가 붙지 않고, 단순한 식별자만 입력해주어야만 한다.
```
template <>
struct is_prime<2> {
  static const bool result = true;
};

template <>
struct is_prime<3> {
  static const bool result = true;
};

template <int N>
struct is_prime {
  static const bool result = !check_div<N, 2>::result;
};

template <int N, int d>
struct check_div {
  static const bool result = (N % d == 0) || check_div<N, d + 1>::result;
};

template <int N>
struct check_div<N, N / 2> {
  static const bool result = (N % (N / 2) == 0);
};
```
### 해결방법
- N을 타입으로 나타내자. 그렇다면 N/2 역시 직접 계산하는 것이 아니라 타입으로 대체할 수 있고, 그에 따라 템플릿 부분 특수화 문제를 해결할 수 있다.
```
template <int N>
struct INT {
  static const int num = N;
};

template <typename a, typename b>
struct add {
  typedef INT<a::num + b::num> result;
};

template <typename a, typename b>
struct divide {
  typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;
```

## 문제2. 의존 타입에 대하여 타입 명시해주기. 
```
template <typename N, typename d>
struct check_div {
  // result 중에서 한 개라도 true 면 전체가 true
  static const bool result =
    (N::num % d::num == 0) || check_div<N, add<d, one>::result>::result;
};

template <typename N>
struct is_prime {
  static const bool result = !check_div<N, two>::result;
};

template <>
struct is_prime<two> {
  static const bool result = true;
};

template <>
struct is_prime<three> {
  static const bool result = true;
};

template <typename N>
struct check_div<N, divide<N, two>::result> {
  static const bool result = (N::num % (N::num / 2) == 0);
};
```
### 해결방법
- 이때 `check_div<N, add<d, one>::result>::result;` 문장과 `struct check_div<N, divide<N, two>::result>` 문장에서 오류가 발생한다. 
- 이유는 컴파일러가 ::result에 대해 '타입'인지, '값' 인지 잘 모르기 때문이다. 
- 따라서 타입의 자리이므로 typename 키워드를 통해 '얘는 타입이야!' 라고 명시 해주어야 한다.
- 이를 통해 INT<5> 은 값이 아닌 타입으로 컴파일이 잘 되게 된다.

# 이해하기!
### 이해가 안 되었던 부분 정리.
1. 첫번째: `add<d, one>::result`, `divide<N, two>::result` 부분에서 컴파일러가 값인지 타입인지를 구분하지 못한다는 것이 잘 이해되지 않았었다.
- 예를 들어 설명한 부분을 보면.
```
template <typename T>
int func() {
  T::t* p;
}

class A {
  const static int t;
};

class B {
  using t = int;
};
```
- 이 예시는 func의 `t`가 클래스(혹은 구조체) A냐 B냐에 따라 값인지 타입인지 바뀔 수 있다는 것을 설명한다.
- A일 땐 `A::t* p;` 이므로 t는 값이 될 것이고, B일 땐 `B::t* p;` 이므로 `p`는 `int*`라는 포인터가 될 것이다.
- <b>따라서 ::result 또한 항상 '타입' 인지 '값'인지를 알 수 없다. 만약 </b>
```
template <>
struct divide<int a, int b> {
  const static int result = a + b;
};
``` 
<b>와 같은 템플릿이 정의 되어있었고, `N`과 `two`가 그냥 `int` 값이었다면, `result`는 `static const int` 값이 되었을 것이다. </b>
- <b>이렇게 템플릿 인자에 따라 타입이 달라질 수 있는 것을 의존타입이라 부른다. 그리고 '타입'임을 알리기 위해서는 반드시 `typename` 이라는 키워드를 통해 알려준다.</b>

2. 두번째: 그렇다면 언제 typename을 꼭 써주어야 하는건가? 다 붙이진 않던데.
- `typename` 키워드는 주로 템플릿 내에 `typedef`를 사용하여 타입을 정의하는 경우에 사용된다. 
- 구조체나 클래스 내부에서 `typedef`로 타입을 정의할 때 `typename`을 사용하면 컴파일러가 타입임을 명확하게 인식한다. 
- 따라서 구조체나 클래스 내부에서 `typedef`로 타입을 정의할 때는 `typename`을 붙여주는 것이 좋은 습관이다.

### 재귀 호출의 선택
- _is_prime<N>을 호출하면 check_div<N, two>::result가 호출됩니다. 
check_div 템플릿의 재귀 호출에서 check_div<N, typename add<d, one>::result>::result와 
check_div<N, typename divide<N, two>::result>::result 중 어떤 것이 먼저 선택되는지 결정되는 것은 템플릿 인스턴스화의 규칙에 따라 결정됩니다.

- 템플릿 인스턴스화에서 컴파일러는 가능한한 가장 특수한 (가장 구체적인) 버전을 선택하려고 노력합니다. 
따라서 컴파일러는 check_div<N, typename divide<N, two>::result>::result가 
check_div<N, typename add<d, one>::result>::result보다 더 특수한 경우로 간주할 것입니다.

- 이 경우 check_div<N, typename divide<N, two>::result>::result는 N을 two로 나눈 결과를 사용하여 소수를 판별하며, 더 일반적인 경우입니다. 
따라서 컴파일러는 이 버전을 먼저 선택합니다. 또한 이러한 선택은 재귀적으로 진행되며, 템플릿 인스턴스화가 가장 특수한 버전을 선택하는 규칙을 따릅니다.

- 따라서 check_div<N, typename divide<N, two>::result>::result가 먼저 선택되며, 이를 통해 N을 two로 나눈 결과를 사용하여 소수 판별이 이루어집니다.