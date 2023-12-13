#include <iostream>

class A
{
private:
    int* data;
public:
    A();
    A(int a) : data(&a){
        std::cout << "일반생성자 호출" << std::endl;
    }
    A(A&& a);
    A& operator=(A&& a);
    ~A();
};

A::A(A&& a)
{
    std::cout << "이동 생성자 호출" << std::endl;
    data = a.data;
    a.data = nullptr;
}
A& A::operator=(A&& a) {
    data=a.data;
    a.data = nullptr;
    return *this;
}
A::~A()
{   
    std::cout << "소멸자호출" << std::endl;
    if(data != nullptr) delete[] data;
}

int main(){
    int&& a = 5;
    // std::cout << a << std::endl;
    A b(1);
    // A c(a);
    // A c(std::move(a));

}