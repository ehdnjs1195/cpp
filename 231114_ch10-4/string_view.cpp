#include <iostream>
#include <string>
/*

    1. string_view는 메모리를 할당하지 않는다.
    2. 문자열을 참조해서 읽기만 하는 것이지요. 
    3. 주의!)따라서 string_view 가 현재 보고 있는 문자열이 소멸된다면 정의되지 않은 작업(Undefined behavior)이 발생하게 됩니다.
*/
void* operator new(std::size_t count) {
    std::cout << count << " bytes 할당 " << std::endl;
    return malloc(count);
}

// 문자열에 "very" 라는 단어가 있으면 true 를 리턴함
bool contains_very(std::string_view str) {  
    return str.find("very") != std::string_view::npos;
}


void ex1() {
    // string_view 생성 시에는 메모리 할당이 필요 없다.
    std::cout << std::boolalpha << contains_very("c++ string is very easy to use")
                << std::endl;

    std::cout << contains_very("c++ string is not easy to use") << std::endl;

    std::string str = "some long long long long long string";
    std::cout << "--------------------" << std::endl;
    std::cout << contains_very(str) << std::endl;
}
void ex2() {    
    std::cout << "string -----" << std::endl;
    std::string s = "sometimes string is very slow";
    std::cout << "--------------------" << std::endl;
    std::cout << s.substr(0, 20) << std::endl << std::endl;

    std::cout << "string_view -----" << std::endl;
    std::string_view sv = s;
    // string_view는 속도 또한 빠르다.
    std::cout << "--------------------" << std::endl;
    std::cout << sv.substr(0, 20) << std::endl;
}

std::string_view return_sv() {
    std::string s = "this is a string";
    std::string_view sv = s;

    return sv;
}
void ex3(){ // 주의사항!
    std::string_view sv = return_sv();  // <- sv 가 가리키는 s 는 이미 소멸됨!

    // Undefined behavior!!!!
    std::cout << sv << std::endl;
    /*
        sv 는 return_sv 안에서 만들어진 s 의 string_view 이지만 함수가
        리턴하면서 지역 객체였던 s 가 소멸하였기 때문에 sv 는 소멸된 문자열을 가리키는 꼴
        따라서 sv 를 사용하면 위와 같이 이상한 결과가 나옵니다 (물론 프로그램을 crash 시킬 수 도 있겠지요). 
        반드시 string_view 가 살아 있는 문자열의 view 인지를 확인하고 사용해야 합니다.
    */
}
int main() {
    // ex1();
    ex2();
    // ex3();
}