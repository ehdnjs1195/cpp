#include <iostream>

void modify_ptr(int* ptr)
{
    *ptr = 100;
}

void modify_ref(int &ref)
{
    ref = 100;
}

int main()
{
    int a = 3;
    // modify(a);   // 주소값을 넘겨줘야 함
    modify_ptr(&a); // a = 100이 됨

    int b = 5;
    modify_ref(b); // b = 100이 됨
}
