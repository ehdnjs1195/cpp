# `remove_if` 이해하기

## 예시) 홀수인 원소들을 처음 2개만 삭제하고자 한다.

```c++
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << "[" << *begin << "] ";
    begin++;
  }
  std::cout << std::endl;
}
struct is_odd {
  int num_delete;

  is_odd() : num_delete(0) {}

  bool operator()(const int& i) {
    if (num_delete >= 2) return false;

    if (i % 2 == 1) {
      num_delete++;
      return true;
    }

    return false;
  }
};
int main() {
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
  vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
  print(vec.begin(), vec.end());
}
```
- 컴파일을 해보면 알 수 있지만, 아래와 같은 결과가 출력된다.
```
처음 vec 상태 ------
[5] [3] [1] [2] [3] [4] 
벡터에서 홀수인 원소 앞의 2개 제거 ---
[2] [3] [4] 
```

- 그렇다면 문제는 무엇일까?
### 문제원인
- 실제 `remove_if`는 대부분의 라이브러리에서 아래와 같이 구현되어 있다.
```c++
template <class ForwardIt, class UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate pred) {
  first = std::find_if(first, last, pred);  // <- pred 한 번 복사됨
  if (first != last)
    // 아래 for 문은 first + 1 부터 시작한다고 봐도 된다 (++i != last)
    for (ForwardIt i = first; ++i != last;)
      if (!pred(*i))  // <-- pred 호출 하는 부분
        *first++ = std::move(*i);
  return first;
}
```
- `find_if`에서 찾은 첫 번째 원소부터 마지막 원소까지 순회하면서 조건을 만족하는 원소를 찾아내어 배열의 앞으로 이동시킨다.
- 문제는  `find_if` 가 함수 객체 `pred` 의 레퍼런스를 받는 것이 아니라, 복사 생성된 버전을 받는다는 점입니다. 
- `find_if`에서 복사된 함수 객체를 사용했기 때문에, 이 함수 객체가 가지고 있는 상태(예: num_delete)가 한 번 이상 초기화되지 않고 누적된 상태를 가지게 됩니다.
- 따라서, `find_if` 호출 후에 아래 `for` 문에서 이미 한 개 원소를 지웠다는 정보가 소멸되게 됩니다. 후에 호출되는 `pred` 들은 이미 `num_delete` 가 1 인지 모른 채 0 부터 다시 시작하게 된다는 점이다.
### 문제해결
- 위와 같은 문제를 해결할 수 있는 방법은 `num_delete`를 객체 `내부 변수`가 아닌 <b>`외부 변수`</b>로 빼는 방법이다.
```c++
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << "[" << *begin << "] ";
    begin++;
  }
  std::cout << std::endl;
}
struct is_odd {
  int* num_delete;

  is_odd(int* num_delete) : num_delete(num_delete) {}

  bool operator()(const int& i) {
    if (*num_delete >= 2) return false;

    if (i % 2 == 1) {
      (*num_delete)++;
      return true;
    }

    return false;
  }
};
int main() {
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
  int num_delete = 0;
  vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd(&num_delete)),
            vec.end());
  print(vec.begin(), vec.end());
}
```
- 코드를 살펴보면 멤버변수를 `포인터`로 받고, 인자를 `참조`하여 받으면 외부 변수로 받게되어, 복사하여 받는것이 아닌 <b>`직접 참조`</b>하게 된다.

## 내가 헷갈리던 점 정리!!
```c++
template <class ForwardIt, class UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate pred) {
  first = std::find_if(first, last, pred);  // <- pred 한 번 복사됨
  if (first != last)
    // 아래 for 문은 first + 1 부터 시작한다고 봐도 된다 (++i != last)
    for (ForwardIt i = first; ++i != last;)
      if (!pred(*i))  // <-- pred 호출 하는 부분
        *first++ = std::move(*i);
  return first;
}
```
### 1. `참조`냐 `값`이냐!
- 우선 `pred`를 세가지로 나누어 보겠다. 
    - 각 객체는 어떻게 다른가 생각해보아야 한다.
    1. 함수 인자로 받고 있는 `UnaryPredicate pred` 부분: `remove_if`의 인자로 받고있는 `pred`로 함수 호출 시에 전달된 객체가 여기 저장된다.
    2. `std::find_if(first, last, pred);`에서 쓰인 `pred` 부분: `std::find_if`내부에서 사용되는 복사본이다.
    3. `for`문 안에 `if (!pred(*i))` 부분: `remove_if`의 인자로 전달받은 `pred`와 같은 객체이다.

- 헷갈리던 이유: 2번에서의 pred가 왜 `복사본`이라는 것인지 이해를 하지 못했다. 
- <b>일반적으로 함수 템플릿은 타입을 추론하여 동작하게 되는데, C++에서 함수 템플릿의 인자로 전달된 객체는 해당 타입으로 복사되어 사용됩니다. 따라서 std::find_if 함수에 전달된 pred는 값(복사본)으로 취급되어 내부에서 사용됩니다.</b>
- <b> std::find_if 함수는 템플릿으로 구현되어 있고, 일반적으로 전달된 조건자를 값으로 받습니다. 따라서 std::find_if에서 복사를 피할 수 없습니다.</b>

### 2. for문의 조건문과 증감문이 합쳐진 형태이다.
- 주석에 잘 나와있듯이 `std::find_of`로 찾은 first가 먼저 `++`되고 시작하기 때문에 `*i`로 `5`가 아닌 `3`이 전달된다. 
    > 따라서 교재 설명중 "for 문에서 이미 한 개 원소를 지웠다는 정보가 소멸되게 됩니다." 라는 설명이 나오게 되는 것이다.

### 3. `pred`가 서로 다르기 때문에 `상태 정보`가 달라진다.
- 앞서 나누었던 `pred`중 2번과 3번의 `pred`객체는 서로 다르다.
- 따라서 `pred`가 실행됨에 따라 `num_delete`의 상태가 변하지만 서로 값이 공유되지 않기 때문에 원하는 결과가 도출되지 않는 것이다.
    > "후에 호출되는 pred 들은 이미 num_delete 가 1 인지 모른 채 0 부터 다시 시작하게 되죠." 라는 설명이 나오는 이유이다.
- 실제로 동작하는 과정을 살펴보면,
    ```c++
    first = std::find_if(first, last, pred); 
    ``` 
    `pred`가 실행되면서 `num_delete`는 `1`이 되고, `first`는 `5`를 가리키는 `iterator`가 반환된다.
    > 그러나 이 `pred` 는 복사본이기 때문에 아래 문장이 실행되는 것과는 다른 `num_delete`을 갖게 되는 것이다.
    ```c++
    for (ForwardIt i = first; ++i != last;)
      if (!pred(*i))  // <-- pred 호출 하는 부분
        *first++ = std::move(*i);
    ```
- `pred`가 실행되면서 이미 `5`는 지워졌지만, `num_delete`에 기록되지 못하고, `num_delete`은 새로 `1`이 된다. 이후 `3`과 `1`이 탈락하면서 결과는 2,3,4만 남게 되는 것이다!