#include <iostream>
#include <memory>

class A : public std::enable_shared_from_this<A> {
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
    // std::shared_ptr<A> get_shared_ptr() { return std::shared_ptr<A>(this); } // this는 자기 자신을 나타내는 포인터임. 즉, 주소. 따라서 아래 설명한대로 문제 발생.
    std::shared_ptr<A> get_shared_ptr() { return shared_from_this(); }
};
/*
    [문제점] shared_ptr<> 의 인자로 주소값이 전달되면 각각의 제어블록이 생성된다!
        ex) A* a = new A();
            std::shared_ptr<A> p1(a);
            std::shared_ptr<A> p2(a);   // 각각의 제어블록생성
        - 이럴 경우 p1이 소멸되면 참조 카운트가 0이 되면서 A의 소멸자가 실행되어 객체 A가 소멸되어버린다.
            하지만 p2가 아직 객체A를 가리키고 있으므로 p2가 소멸될 때 문제가 발생한다.
        - 따라서 shared_ptr를 주소값을 통해 생성하는 것을 지양해야 한다.
        
        - 하지만, 객체 내부에서 자기 자신을 가리키는 shared_ptr를 만들때 this를 사용할 수 있다. 
        - 따라서 이를 해결할 수 있는 enable_shared_from_this 상속받는다.
            - shared_ptr생성: `shared_from_this()`함수
            - shared_from_this는 제어블록을 확인만 할 뿐, 없는 제어블록을 만들지는 않는다. 주의!

*/

int main() {
    std::shared_ptr<A> pa1 = std::make_shared<A>();
    std::shared_ptr<A> pa2 = pa1->get_shared_ptr(); // 반드시 shared_ptr가 먼저 정의되어 있어야 한다.

    std::cout << pa1.use_count() << std::endl;
    std::cout << pa2.use_count() << std::endl;
}