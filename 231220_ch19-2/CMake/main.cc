#include <iostream>

#include "foo.h"

int main() {
  int i;  // 컴파일 옵션이 들어갔기 때문에 make에서 빌드되지 않고 오류가 발생한다.
  std::cout << "Foo : " << foo() << std::endl;
  return 0;
}