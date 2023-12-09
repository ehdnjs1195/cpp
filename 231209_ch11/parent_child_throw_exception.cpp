#include <exception>
#include <iostream>

class Parent : public std::exception {
  public:
    
    // what 은 std::exception 에 정의된 함수로, 이 예외가 무엇인지 설명하는 문자열을
    // 리턴하는 함수 입니다.
    virtual const char* what() const noexcept override { return "Parent!\n"; }
};

class Child : public Parent {
  public:
    const char* what() const noexcept override { return "Child!\n"; }
};

int func(int c) {
    if (c == 1) {
        throw Parent(); 
    } else if (c == 2) {
        throw Child();
    }
    return 0;
}

int main() {
    int c;
    std::cin >> c;
    /*
        [catch를 Parent -> Child 순으로 할 경우]
        ex)
            try {
                func(c);
            } catch (Parent& p) {
                std::cout << "Parent Catch!" << std::endl;
                std::cout << p.what();
            } catch (Child& c) {
                std::cout << "Child Catch!" << std::endl;
                std::cout << c.what();
            }
        
        중요개념, catch 문의 경우 가장 먼저 대입될 수 있는 객체를 받는다!
        Parent& p = Child(); 는 가능하기 때문에 Parent catch 가 먼저 받아버리는 것입니다.
        따라서 2를 입력했을 때 Child객체를 캐치하지 못하고, Parent를 캐치하여 Parent Catch!문이 출력되게 된다.

        =>이를 방지하기 위해 언제나 Parent catch 를 Child catch 보다 뒤에 써주는 것이 좋습니다.
    */
    try {
        func(c);
        
    } catch (Child& c) {
        std::cout << "Child Catch!" << std::endl;
        std::cout << c.what();
    } catch (Parent& p) {
        std::cout << "Parent Catch!" << std::endl;
        std::cout << p.what();
    }
}