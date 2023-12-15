#include "AutoPtr.hpp"
#include "Resource.hpp"
#include "Timer.hpp"
/*
    std::move함수: 사용자가 move semantics를 사용하고자 할 때 쓸 수 있는 함수.
    - 인자로 받는 객체의 R-value를 반환해줌 
*/

template <class T>
void MySwap(T &a, T &b)
{
    // copy
    // T tmp = a;  //copy constructor
    // b = a;      //copy assignment
    // a = tmp;    //copy assignment

    // move
    T tmp(std::move(a)); // move constructor
    b = std::move(a);    // move assignment
    a = std::move(tmp);  // move assignment
}

AutoPtr<Resource> generateResource()
{
    AutoPtr<Resource> res(new Resource(10000000));

    return res;
}

int main()
{
    // move함수를 써보고 move semantics 사용해보기
    // {
    //     AutoPtr<Resource> res1(new Resource(10000000));

    //     cout << res1.m_ptr << endl;

    //     // AutoPtr<Resource> res2 = res1;  // copy semantics 사용함.
    //     AutoPtr<Resource> res2 = std::move(res1);  // move semantics 사용함. move assignment operator가 실행됨.
            // 이후에는 res1은 데이터가 없으므로, 더이상 접근할 수 없음. 주의할 것!!

    //     cout << res1.m_ptr << endl;
    //     cout << res2.m_ptr << endl; // 새로운 주소를 가지며 내부적으로 전체가 복사된 모양임.
    // }


    // MySwap 함수를 이용해서 copy, move를 비교해보기
    // {
    //     AutoPtr<Resource> res1(new Resource(3));
    //     res1->setAll(3);

    //     AutoPtr<Resource> res2(new Resource(5));
    //     res2->setAll(5);

    //     res1->print();
    //     res2->print();

    //     MySwap(res1, res2);
        
    //     res1->print();
    //     res2->print();
    // }

    // move semantics는 std에 거의 구현이 되어있다.
    // {
    //     vector<string> v;
    //     string str = "Hello";

    //     v.push_back(str);   // push_back에 마우스를 올려보면 & 하나만 있는 것을 알 수 있다. => str을 l-value로 받는다는 뜻. 즉 변수로 받는다.

    //     cout << str << endl;
    //     cout << v[0] << endl;

    //     v.push_back(std::move(str));    // 마찬가지로 마우스를 올려보면 &&로 오버로딩됨. => str을 r-value reference로 받는다는 뜻.
        
    //     cout << str << endl;    // 출력하면 빈칸이 나오는 것을 알 수 있음. => str이 v[1]으로 move되어서 내용이 없어짐.
    //     cout << v[0] << " " << v[1] << endl;
    //     // std에서는 별도로 r-value를 받는 함수들이 구현되어 있는것을 알 수 있다.
    // }


    //
    {
        std::string x{"abc"};
        std::string y{"de"};

        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;

        MySwap(x, y);   // copy와 move 작동의 주석을 바꿔가며 실행해보고, 디버깅 하면서 실행해볼것.

        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
    }

    return 0;
}