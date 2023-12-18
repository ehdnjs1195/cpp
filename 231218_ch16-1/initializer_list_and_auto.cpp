#include <initializer_list>
#include <string>
/*
    ### C++ 17 부터 아래와 같이 두 가지 형태로 구분
    1. auto x = {arg1, arg2...} 형태의 경우 arg1, arg2 ... 들이 모두 같은 타입이라면 x 는 std::initializer_list<T> 로 추론됩니다.
    2. auto x {arg1, arg2, ...} 형태의 경우 만일 인자가 단 1 개라면 인자의 타입으로 추론되고, 여러 개일 경우 오류를 발생시킵니다.

    문자열을 다룰 때
    - auto list = {"a", "b", "cc"}; initializer_list<std::string> 이 아닌 initializer_list<const char*> 이 된다는 점
*/
int main()
{
    auto a = {1};    // 첫 번째 형태이므로 std::initializer_list<int>
    auto b{1};       // 두 번째 형태 이므로 그냥 int
    auto c = {1, 2}; // 첫 번째 형태이므로 std::initializer_list<int>
    // auto d{1, 2};    // 두 번째 형태 인데 인자가 2 개 이상이므로 컴파일 오류

    using namespace std::literals; // 문자열 리터럴 연산자를 사용하기 위해 추가해줘야함.

    auto list = {"a"s, "b"s, "c"s}; // C++ 14 에서 추가된 리터럴 연산자 || initializer_list<std::string>로 추론된다.
}