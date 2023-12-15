#include <iostream>
#include <memory>
#include "Resource.hpp"

auto doSomething()
{
    // 방법1
    // auto res1 = std::make_unique<Resource>(5);
    // return res1;

    // 방법2
    // return std::unique_ptr<Resource>(new Resource(5));

    // 방법3. 가장 간단함
    return std::make_unique<Resource>(5);   //내부적으로 소유권이 move semantics로 넘어가기 때문에 빠름.
}


// 1. std::unique_ptr<Resource> & res 여기서 &를 빼고 unique_ptr를 인자로 받고자 한다면 컴파일 오류가 발생한다.
// 이유는 함수 인자로 전달할 때는 copy sematics가 기본이기 때문에
// 2. 혹은 doSomething(std::move(인자)) 와 같이 호출할 수 있다.
// 3. return으로 unique_ptr를 돌려줘서 소유권을 다시 돌려주는 형태도 많이 사용함.
auto doSomething2(std::unique_ptr<Resource> res)
{
    res->setAll(100);
    res->print();
    return res;
}

void doSomething3(Resource * res)   // 포인터만 넘겨주고 작업을 맡기는 경우
{
    res->setAll(100);
    res->print();
}


int main()
{
    // 1. unique_ptr개념.
    // {
    //     // Resource *res = new Resource(10000000);

    //     std::unique_ptr<Resource> res(new Resource(10000000));  // 알아서 소멸자를 소출해줌. scope를 벗어나면서
    //     // early return or throw

    //     // delete res;
    // }

    // 2. unique_ptr 사용법 배우기.
    // {
    //     std::unique_ptr<int> upi(new int);

    //     // std::unique_ptr<Resource> res1(new Resource(5));
    //     auto res1 = std::make_unique<Resource>(5);  // 위와 같은 내용. 생성자를 직접 호출해서 만들어줌.
    //     // auto res1 = doSomething();  // 함수를 통해서도 만들 수 있다.

    //     res1->setAll(5);
    //     res1->print();

    //     std::unique_ptr<Resource> res2;

    //     std::cout << std::boolalpha;
    //     std::cout << static_cast<bool>(res1) << std::endl;  // null값이냐 아니냐를 bool로 캐스팅해서 볼 수 있음.
    //     std::cout << static_cast<bool>(res2) << std::endl;  // 현재 null 이므로 false

    //     // res2 = res1;         // unique_ptr는 복사가 되지 않는다.
    //     res2 = std::move(res1); // move semantics만 사용할 수 있다.

    //     std::cout << std::boolalpha;
    //     std::cout << static_cast<bool>(res1) << std::endl;  // 소유권을 넘김
    //     std::cout << static_cast<bool>(res2) << std::endl;  // true 출력될 것임.

    //     if(res1 != nullptr) res1->print();
    //     if(res2 != nullptr) res2->print();  // (*res).print();  여기서 출력됨.
    // }

    // 3. unique_ptr의 소유권을 주고 받는 방식 용법
    {
        auto res1 = std::make_unique<Resource>(5);
        res1->setAll(1);
        res1->print();

        std::cout << std::boolalpha;
        std::cout << static_cast<bool>(res1) << std::endl;  // 소유권을 넘김

        // res1 = doSomething2(std::move(res1)); //l-value reference를 전달하고 있다.
        doSomething3(res1.get());   // Resource 타입의 unique_ptr가 내부적으로 가지고 있는 Resource의 포인터를 가져오는 함수. => l-value로 넘겨주는 것과 같은 작동이 됨.

        std::cout << std::boolalpha;
        std::cout << static_cast<bool>(res1) << std::endl;  // 소유권을 넘김
        res1->print();   //함수의 return이 없으면 res1의 소유권이 없으므로 print()함수를 호출할 수 없게됨. Segmentation fault 나옴.
    }

    // 4. unique_ptr 사용의 주의점
    {
        Resource *res = new Resource;
        std::unique_ptr<Resource> res1(res);
        std::unique_ptr<Resource> res2(res);    // 경고: unique_ptr의 소유권을 또 할당하면, 두번 지우려 시도하기 때문에 문제가 발생함

        delete res; // 경고: unique_ptr에서 알아서 지워주는데 또 지우려 시도하면 문제가 발생함.(습관적으로 발생할 수 있는 문제.)
    }
}