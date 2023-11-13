# Set 이해하기
- set은 기본적으로 타입(클래스)에 대해 정의되고 저장할 때, 해당 클래스가 `operator<`를 제공해야 한다.
- 기본적으로 오름차순 정렬을 사용하며, 각 원소들 간에 비교 연산이 필요함.
- `<` 연산자를 기본적으로 사용하여 이루어진다.

## 외브 라이브러리를 사용할 때, `operator<`가 정의되어 있지 않는 경우
- set은 해당 클래스의 객체를 비교할 수 없다고 판단하고 컴파일 오류가 발생한다.
- set은 비교 연산을 정의해주어야 하므로 이를 위해 별도의 비교함수나 구조체를 만들어 사용하거나, 함수 객체를 사용할 수 있다.
- 이 예제는(set_2.cpp) 함수 객체를 이용하여 comparator를 만들어 비교연산을 구현한 예시이며, 아래는 이를 정리한 예시이다.

```
#include <iostream>
#include <set>

class ExternalClass {
public:
    int data;

    ExternalClass(int value) : data(value) {}
    // 이 클래스에는 operator<가 정의되어 있지 않음
};

struct ExternalClassComparator {
    bool operator()(const ExternalClass& lhs, const ExternalClass& rhs) const {
        return lhs.data < rhs.data;
    }
};

int main() {
    std::set<ExternalClass, ExternalClassComparator> externalSet;
    externalSet.insert(ExternalClass(3));
    externalSet.insert(ExternalClass(1));
    externalSet.insert(ExternalClass(2));

    // externalSet을 출력
    for (const auto& elem : externalSet) {
        std::cout << elem.data << " ";
    }

    return 0;
}
```
- 예시를 보면, ExternalClassComparator 구조체가 set객체의 comparator로 작용하는 것을 볼 수 있다.

## TodoCmp 의 `operator()` 함수가 어떻게 호출되는지 설명(출처:GPT)

1. **원소 추가 (`insert` 함수):**
    - **`std::set`**은 새로운 원소를 추가할 때마다 트리를 순회하여 정렬된 위치를 찾아갑니다.
    - 원소가 비어있는 경우, 그냥 삽입됩니다.
    - 비어있지 않은 경우, 비교 함수인 **`TodoCmp`**의 **`operator()`** 함수를 호출하여 새로운 원소를 기존의 원소와 비교합니다.
    - 비교 함수는 두 **`Todo`** 객체를 비교하여 정렬 순서를 결정합니다.
    - 비교 함수의 반환값이 **`true`**이면 새로운 원소가 현재 위치보다 작으므로 왼쪽 서브트리로 이동하고, **`false`**이면 크므로 오른쪽 서브트리로 이동합니다.
    - 이와 같은 과정을 반복하여 정렬된 위치를 찾아 삽입합니다.

예를 들어, 아래는 **`todos.insert(Todo(1, "농구 하기"));`**를 호출하는 경우의 순서입니다.

- 비어있는 **`todos`**에 **`Todo(1, "농구 하기")`**를 삽입합니다.
- **`TodoCmp::operator()`** 함수는 호출되며, 비교 대상이 없으므로 삽입됩니다.

다른 예로, **`todos.insert(Todo(2, "수학 숙제 하기"));`**를 호출하는 경우:

- **`Todo(2, "수학 숙제 하기")`**와 기존의 **`Todo`** 객체들을 비교하여 정렬 순서를 결정합니다.
- **`TodoCmp::operator()`** 함수가 호출되며, 두 번째 인자로 **`Todo(2, "수학 숙제 하기")`**가 전달됩니다.
- **`operator()`** 함수에서 중요도가 같으므로 **`job_desc`**를 비교합니다.
- **`"수학 숙제 하기"`**가 **`"농구 하기"`**보다 사전적으로 뒤에 오므로 **`operator()`** 함수는 **`true`**를 반환합니다.
- 따라서 **`Todo(2, "수학 숙제 하기")`**는 **`Todo(1, "농구 하기")`**보다 작은 값으로 판정되어 왼쪽 서브트리로 이동합니다.
- 이런식으로 원하는 위치를 찾아가면서 삽입이 이루어집니다.

이러한 과정을 통해 **`std::set`**은 원소를 정렬된 상태로 유지하며, **`TodoCmp`**의 **`operator()`** 함수를 활용하여 비교하고 정렬합니다.