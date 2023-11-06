#include <iostream>
#include <string>
#include <cstring>

// 첫번째 시도 
template <typename String>
std::string StrCat(const String& s) {
    return std::string(s);
}

template <typename String, typename... Strings>
std::string StrCat(const String& s, Strings... strs) {
    return std::string(s) + StrCat(strs...);
}
void ex1() {
    // std::string과 const char* 을 혼합해서 사용 가능하다.
    std::cout << StrCat(std::string("this"), " " ,"is", " ", std::string("a"), " ", std::string("setence"));
    // 그러나 이 방식은 std::string 의 operator+를 매번 호출하는 셈이기 때문에 메모리 할당이 최대 5번씩이나 일어날 수 있다.
    // 매우 비효율 적!
    /*
        개선방안
        1. 합쳐진 문자열의 길이를 먼저 계산하기
        2. 메모리를 할당하기
        3. 문자열 붙이기
    */
}

// 두번째 시도
// 문자열 전체 사이즈를 가져오는 함수
size_t GetStringSize(const char* s) {return strlen(s);}
size_t GetStringSize(const std::string& s) {return s.size();}
// const char* 과 std::string 모두 잘 작동하게 하기 위해서 두가지 모두를 오버로딩하여 만듬
template <typename String, typename... Strings>
size_t GetStringSize(const String& s, Strings... strs) {
    return GetStringSize(s) + GetStringSize(strs...);
}

// 문자열을 붙여주는 함수 정의
void AppendToString(std::string* concat_str) { return; }

template <typename String, typename... Strings>
void AppendToString(std::string* concat_str, const String& s, Strings... strs) {
  concat_str->append(s);
  AppendToString(concat_str, strs...);
}

// 최종 코드
template <typename String, typename... Strings>
std::string StrCat2(const String& s, Strings... strs) {
    // 1. 먼저 합쳐질 문자열의 총 길이 구하기
    size_t total_size = GetStringSize(s, strs...);

    // 2. 메모리 할당하기
    std::string concat_str;
    concat_str.reserve(total_size);

    // 3. 문자 합치기
    concat_str = s; // 첫문자
    AppendToString(&concat_str, strs...);
    
    return concat_str;
}

void ex2() {
    std::cout << StrCat2(std::string("this"), " " ,"is", " ", std::string("a"), " ", std::string("setence"));
}

int main() {
    // ex1();
    ex2();
}