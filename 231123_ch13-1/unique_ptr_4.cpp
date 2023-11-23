#include <iostream>
#include <memory>

class A {
    int* data;

    public:
    A() {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
    }

    void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }

    void do_sth(int a) {
        std::cout << "무언가를 한다!" << std::endl;
        data[0] = a;
    }

    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

// 올바르지 않은 전달 방식
void do_something_wrong(std::unique_ptr<A>& ptr) {  // unique_ptr 레퍼런스 자체를 전달받는다.
    ptr->do_sth(3); 
    /*
        내부로 전달은 잘 되지만 레퍼런스(&: 주소값)로 unique_ptr를 전달했다면, 함수 내부에서 ptr은 더이상 유일한 소유권을 의미하지 않는다.
        pa 가 유일하게 소유하고 있던 객체는 이제, 적어도 do_something 함수 내부에서는 ptr 을 통해서도 소유할 수 있게 된다는 것입니다. 
        즉, unique_ptr 은 소유권을 의미한다는 원칙에 위배되는 것이지요.
        따라서, unique_ptr 의 레퍼런스를 사용하는 것은 unique_ptr 를 소유권 이라는 중요한 의미를 망각한 채 단순히 포인터의 단순한 Wrapper 로 사용하는 것에 불과합니다.
         => 의미를 곱씹어볼 필요가 있음..
    */
}
// 일반적인 포인터를 받도록하여 객체에 접근할 수 있는 권한을 부여한다.
void do_something(A* ptr) { ptr->do_sth(3); }

int main() {
    std::unique_ptr<A> pa(new A());
    // do_something_wrong(pa);
    do_something(pa.get()); // 올바른 접근. get을 통해 unique_ptr의 주소값을 리턴하여 준다.
    
}