#include <string>
#include <iostream>

using namespace std::literals;

void literal() {
    auto s1 = "hello"s; 
    /*
        std::string operator"" s(const char *str, std::size_t len); 를 정의한 것.  => ""뒤에 s가 붙으면 문자열로 타입을 인식한다.
        "hello"s -> operator""("hello", 5);로 바뀌게 됨.
        만약 없으면? C에서와 같이 const char * 로 인식한다.
    */
    std::cout << "s1의 길이: " << s1.size() << std::endl;

    std::string str =  "hello";     // char[]
    std::wstring wstr = L"hello";   // wchar_t[]        => wchar_t문자열을 만들고 싶으면 L을 앞에 붙여준다.

}
void raw_string_literal() {
    std::string str = R"(asdfasdf
    이 안에는
    어떤 것들이 와도
    // 이런것도 되고
    #define hasldifjsoifpa
\n\n   <----- Escape 안해도 됨
    )";

    std::cout << str << std::endl;
    std::cout << "--------------" << std::endl;

    // )" 로 닫아주어야 하기때문에 이를 문자열안에 넣을 수 없다는 문제점이 있다.
    
    // 해결방법
    // R"/* delimiter */( /* 문자열 */ )/* delimiter */"   꼴로 쓰면 된다.
    /*
        delimiter 자리는 아무것도 없어도 되고, 위처럼 여러분이 원하는 문자열이 와도 되는데, 
        앞의 delimiter 와 뒤의 delimiter 는 같아야 합니다. 
        문법이 복잡하다고 느끼신다면 그냥 "delimiter( 가 하나의 괄호라고 생각하시면 됩니다.
    */ 
    std::string foo_str = R"foo(
    )"; <-- 무시됨
    )foo";
    std::cout << foo_str << std::endl;

}
int main() {
    // literal();
    raw_string_literal();

}