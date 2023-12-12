#include <string>
#include <iostream>
#include <cstring>

class MyString
{
private:
    /* data */
    char* string_content;
    int string_length;
    int memory_capacity;
public:
    MyString();                             // 일반생성자
    MyString(const char *str);              // 일반생성자(문자열로 생성)
    MyString(const MyString &s);            // 복사생성자
    MyString(MyString &&s);                 // 이동생성자
    MyString &operator=(const MyString &s); // 일반 대입연산자
    MyString& operator=(MyString&& s);      // 이동 대입연산자
    ~MyString();                            // 소멸자
};

MyString::MyString()
{
    std::cout << "일반 생성자" << std::endl;
    string_content = NULL;
    string_length = 0;
    memory_capacity = 0;
}
MyString::MyString(const char *s) {
    std::cout << "일반 생성자" << std::endl;
    string_length = strlen(s);
    memory_capacity = string_length;
    string_content = new char[string_length];

}
MyString::MyString(const MyString &s) {
    std::cout << "복사 생성자" << std::endl;
    string_length = s.string_length;
    memory_capacity = s.memory_capacity;
    string_content = new char[string_length];
    for(int i=0; i<s.string_length; i++) {
        string_content[i] = s.string_content[i];
    }
}

MyString::MyString(MyString &&s){   // MyString &&s: rvalue reference | s: lvalue
    std::cout << "이동 생성자" << std::endl;
    string_length = s.string_length;
    memory_capacity = s.memory_capacity;
    string_content = s.string_content;  // copy address

    s.string_content = nullptr;     // 해제 하지 못하도록
    s.string_length = 0;
    s.memory_capacity = 0;
}
MyString &MyString::operator=(const MyString &s) {
    std::cout << "복사" << std::endl;
    if(s.string_length > memory_capacity) {
        delete[] string_content;
        string_content = new char[s.string_length];
        memory_capacity = s.string_length;
    }
    string_length = s.string_length;
    for(int i = 0; i != string_length; i++) {
        string_content[i] = s.string_content[i];
    }
    return *this;
}

MyString& MyString::operator=(MyString&& s) {
    std::cout << "이동" << std::endl;
    string_content = s.string_content;
    string_length = s.string_length;
    memory_capacity = s.memory_capacity;
    
    s.string_content = nullptr;
    s.memory_capacity = 0;;
    s.string_length = 0;
    return *this;
}

MyString::~MyString()
{
    if(string_content) delete[] string_content;
}

