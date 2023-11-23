#include <iostream>
#include <memory>
#include <vector>

class A {
    int *data;

    public:
    A(int i) {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
        data[0] = i;
    }

    void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }
    void some2() { std::cout << "값 : " << data[0] << std::endl; }
    ~A() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void ex1() {
    std::vector<std::unique_ptr<A>> vec;
    std::unique_ptr<A> pa(new A(1));

    // vec.push_back(pa);  // vector의 push_back은 전달된 인자를 복사해서 집어넣기 때문에, unique_ptr의 복사 생성자에 접근하였기 때문에 오류가 발생한다!!

    // 이를 방지하기 위해서는 명시적으로 pa 를 vector 안으로 이동 시켜주어야만 합니다(move). 즉 push_back 의 우측값 레퍼런스를 받는 버전이 오버로딩 될 수 있도록 말이지요.
    vec.push_back(std::move(pa));  // 잘 실행됨.
}
void ex2() {
    std::vector<std::unique_ptr<A>> vec;

    // vec.push_back(std::unique_ptr<A>(new A(1))); 과 동일
    // 불필요한 이동 과정을 생략할 수 있다.
    vec.emplace_back(new A(1));
    /*
        emplace_back 함수는 전달된 인자를 완벽한 전달(perfect forwarding) 을 통해, 
        직접 unique_ptr<A> 의 생성자에 전달 해서, vector 맨 뒤에 unique_ptr<A> 객체를 생성해버리게 됩니다.
        따라서, 위에서 처럼 불필요한 이동 연산이 필요 없게 됩니다 (왜냐하면 vector 맨 뒤에 생성하기 때문에!)
    */
    vec.back()->some2();
}

int main() {
    // ex1();
    ex2();
}