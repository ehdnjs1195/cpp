#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

class Object
{
public:
    void hello(const string& s) {
        cout << "Hello " << s << endl;
    }
};
void goodbye(const string& s) {
    cout << "Goodbye " << s << endl;
}
int main() {
    // 1. 람다함수 정의
    auto func = [](const int& i) -> void {cout << "Hello, World!" << endl; };
    // func(123);

    // 람다함수의 진정한 의미는 이렇게 함수의 이름이 없을 때이다.
    [](const int& i) -> void {cout << "Hello, World!" << endl; } (1234);

    {
        // 2. 람다 함수 변수 참조
        string name = "JackJack";
        [&]() {cout << name << endl;};
        // &는 람다 함수가 정의된 블록 내에서(스코프 내에서) 정의된 변수에 접근할 수 있게하는 표시.
        // [this]: 클래스의 멤버로 정의
        // [=]: 카피
    }

    vector<int> v;
    v.push_back(1);
    v.push_back(2);

    // 3. stl에서 사용. 
    auto func2 = [](int val) {cout << val << endl;};    // 람다 함수에서 리턴타입이 void 일 경우는 생략하는 것이 편함.
    // for_each(v.begin(), v.end(), func2);    //람다 함수를 사용해서 stl에 사용하기
    for_each(v.begin(), v.end(), [](int val) {cout << val << endl;}); // 바로 함수로 넣어리는 형태가 더 많음

    // 4. 
    cout << []() -> int {return 1;} () << endl;

    // #std::function => function pointer를 체계화.
    std::function<void(int)> func3 = func2; // 함수를 변수처럼 주고받을 수 있음.
    func3(123); // 마치 functor 처럼 실행 시킴.

    // #std::bind
    std::function<void()>func4 = std::bind(func3, 456); // func4는 파라미터가 없음. func3와 바로 묶어둠.
    func4();
    


    // placeholder : 파라미터가 여러개 있을 때 사용할 수 있음.
    {
        Object instance;
        auto f = std::bind(&Object::hello, &instance, std::placeholders::_1);   
        // hello라는 함수를 실행 시켜라, 그런데 함수를 실행시키기 위해서는 그 멤버함수를 가지고 있는 객체가 필요함. Object 클래스의 &instance!
        // hello라는 함수가 파라미터가 1개임. => placeholders로 1개 지정.
        f(string("World!!"));
        f("Dowon");


        auto f2 = std::bind(&goodbye, std::placeholders::_1);   // 함수를 바로 바인딩할 수 있다.
        f2(string("World"));
    }


}