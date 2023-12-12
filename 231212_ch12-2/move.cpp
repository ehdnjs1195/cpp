#include <iostream>
#include <cstring>

class MyString {
    char *string_content;  // 문자열 데이터를 가리키는 포인터
    int string_length;     // 문자열 길이

    int memory_capacity;  // 현재 할당된 용량

 public:
    MyString();

    // 문자열로 부터 생성
    MyString(const char *str);

    // 복사 생성자
    MyString(const MyString &str);

    // 이동 생성자
    MyString(MyString &&str);

    // 일반적인 대입 연산자
    MyString &operator=(const MyString &s);

    // 이동 대입 연산자
    MyString& operator=(MyString&& s);

    ~MyString();

    int length() const;

    void println();
};

MyString::MyString() {
    std::cout << "생성자 호출 ! " << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = NULL;
}

MyString::MyString(const char *str) {
    std::cout << "생성자 호출 ! " << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString &str) {
    std::cout << "복사 생성자 호출 ! " << std::endl;
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}
MyString::MyString(MyString &&str) {
    std::cout << "이동 생성자 호출 !" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    // 임시 객체 소멸 시에 메모리를 해제하지
    // 못하게 한다.
    str.string_content = nullptr;
    str.string_length = 0;
    str.memory_capacity = 0;
}
MyString::~MyString() {
    if (string_content) delete[] string_content;
}
MyString &MyString::operator=(const MyString &s) {
    std::cout << "복사!" << std::endl;
    if (s.string_length > memory_capacity) {
        delete[] string_content;
        string_content = new char[s.string_length];
        memory_capacity = s.string_length;
    }
    string_length = s.string_length;
    for (int i = 0; i != string_length; i++) {
        string_content[i] = s.string_content[i];
    }

    return *this;
}
MyString& MyString::operator=(MyString&& s) {
    std::cout << "이동!" << std::endl;
    string_content = s.string_content;
    memory_capacity = s.memory_capacity;
    string_length = s.string_length;

    s.string_content = nullptr;
    s.memory_capacity = 0;
    s.string_length = 0;
    return *this;
}
int MyString::length() const { return string_length; }
void MyString::println() {
    for (int i = 0; i != string_length; i++) std::cout << string_content[i];

    std::cout << std::endl;
}

template <typename T>
void my_swap(T &a, T &b) {
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}
/*
    move 함수
    - 인자로 받은 객체를 우측값으로 변환해서 리턴해준다.
    - 타입 변환만 수행할 뿐임.
    - 강제적으로 우측값 레퍼런스를 인자로 받는 이동생성자를 호출할 수 있게 해준다.
    
    [장점]
    1. 예를 들어 문자열이나 동적 배열을 가진 클래스의 객체를 복사하는 경우, 해당 자원을 복사하는 것은 비용이 많이 들 수 있다. 이런 상황에 포인터만 복사해서 소유권을 이전함으로서 효율적으로 작업할 수 있다.
    2. 따라서 복사보다 빠른 성능을 기대할 수 있다.
    [주의]
    1. 이동된 객체는 이후 원래 객체와 상태가 다를 수 있기 때문에 사용전에 유효성을 확인해야한다. (이전에 vector예제와 같은.)
    2. 따라서 주소값이 메모리에서 사라지지 않도록 주의할 것.
*/
int main() {
    MyString str1("abc");
    MyString str2("def");
    std::cout << "Swap 전 -----" << std::endl;
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();

    std::cout << "Swap 후 -----" << std::endl;
    my_swap(str1, str2);
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();
}