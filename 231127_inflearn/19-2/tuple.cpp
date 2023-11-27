#include <iostream>
#include <tuple>

using namespace std;

// 정석!
tuple<int, int> my_func()
{
    return tuple<int, int>(123,456);
}

// auto로 반환타입 편하게 쓰기
auto my_func2()
{
    return tuple<int, int, int>(123,456, 789);
}

// return 에 제네릭 타입도 생략 가능
auto my_func3()
{
    return tuple(123,456,789,10);
}
int main()
{
    // tuple<int,int> result = my_func();
    auto result = my_func2();   // auto로 간편하게 쓸 수 있음.

    // cout << std::get<0>(result) << " " << get<1>(result) << get<2>(result) << endl;

    auto[a,b,c,d] = my_func3();    // 변수 a,b,c,d를 선언하면서 받는것과 같은 형태임.
    cout << a << " " << b << " " << c << " " << d << endl;
    return 0;
}