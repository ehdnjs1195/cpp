#include <iostream>
#include "Resource.hpp"
//shared_ptr는 객체를 가리키는 포인터가 몇개인지 센다.
int main()
{
    // Resource * res = new Resource(3);
    // res->setAll(1);
    {
        // std::shared_ptr<Resource> ptr1(res);    // 1. pointer를 넣어서 생성하는 방법

        auto ptr1 = std::make_shared<Resource>(3);   // 2. make_shared를 통해 만들면 더 안전하고 편리하다.
        ptr1->setAll(1);

        ptr1->print();

        {
            // std::shared_ptr<Resource> ptr2(ptr1);
            // std::shared_ptr<Resource> ptr2(res);
            /*
                <주의점!>
                ptr2를 만들때 res를 직접 부여하여 생성하면, ptr1이 또 다른 소유권이 있는지 상태를 모른다.
                그래서 ptr2가 현재 scope에서 객체를 먼저 소멸시키고 ptr1이 다음 scope에서 객체를 사용하고, 소멸시키려 할 때 문제가 발생한다.
                따라서 make_shared를 통해 만드는 것을 더 선호하고, 안전한다.
            */
            auto ptr2 = ptr1;   // 따라서 이게 깔끔한 방법!

            ptr2->setAll(3);
            ptr2->print();

            std::cout << "Going out of the block" << std::endl;
        }
        //ptr1은 바로 위 {} scope 보다 밖에서 만들어졌던 것이기 때문에 여전히 소유권이 살아있음.
        ptr1->print();
        std::cout << "Going out of the outer block" << std::endl;
    }   // 여기 scope를 벗어나고 나서야 Resource가 소멸된다.(ptr1이 소멸되면서 resource 해제.)

    return 0;
}