// 복사생성자는 몇번 호출될까
#include <iostream>

class A {
  int x;

 public:
  A(int c) : x(c) {}
  A(const A& a) {
    x = a.x;
    std::cout << "복사 생성" << std::endl;
  }
};

class B {
  A a;

 public:
  B(int c) : a(c) {}
  B(const B& b) : a(b.a) {}
  A get_A() {
    A temp(a);
    return temp;
  }
};

int main() {
  B b(10);  // 복사 생성 X

  std::cout << "---------" << std::endl;
  A a1 = b.get_A(); // 일반적으로 여기서 2번이지만, gcc나 컴파일러에 따라 반환값 최적화 과정으로 1번만 호출된다.
}