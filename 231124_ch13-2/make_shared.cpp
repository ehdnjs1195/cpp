#include <iostream>
#include <memory>
#include <vector>

class A {
    int *data;

    public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    ~A() {
        std::cout << "소멸자 호출!" << std::endl;
        delete[] data;
    }
};

int main() {
    std::shared_ptr<A> p1(new A());    // 동적 할당을 두번하게됨. A를 생성할 때 한번, 제어블록 할당 한번.
    // 동적할당은 꽤 큰 연산작업이 필요하다.
    // 따라서 아예 두 개를 합친 크기로 한 번 할당하는 것이 훨씬 빠르다.
    std::shared_ptr<A> mk_a = std::make_shared<A>();
}