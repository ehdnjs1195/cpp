#include <iostream>
#include <string>

// 이와 같이 new 를 전역 함수로 정의하면 모든 new 연산자를 오버로딩 해버린다.
// (어떤 클래스의 멤버 함수로 정의하면 해당 클래스의 new 만 오버로딩됨)
void* operator new(std::size_t count) {
    std::cout << count << " bytes 할당 " << std::endl;
    return malloc(count);
}

int main() {
    std::cout << "s1 생성 --- " << std::endl;
    std::string s1 = "this is a pretty long sentence!!!";
    std::cout << "s1 크기 : " << sizeof(s1) << std::endl;
    /*
        s1을 생성할 때 메모리 할당이 발생.      => 동적할당 O   => new라는 키워드가 동적 메모리 할당이므로.
        s2는 메모리 할당 x. => 객체로만 생성.   => 동적할당 X

        하지만 s2의 크기가 32로 꽤 큰편이고, 성능 향상을 기대할 수 있다.
    */

    std::cout << "s2 생성 --- " << std::endl;
    std::string s2 = "short sentence";
    std::cout << "s2 크기 : " << sizeof(s2) << std::endl;
}