#include <iostream>
#include "AutoPtr.hpp"
#include "Resource.hpp"


using namespace std;
int main() {
    AutoPtr<Resource> res1(new Resource);
    AutoPtr<Resource> res2;

    cout << std::boolalpha;

    cout << res1.m_ptr << endl;
    cout << res2.m_ptr << endl;
    res2 = res1;    //move semantics

    cout << res1.m_ptr << endl;
    cout << res2.m_ptr << endl;
    /*
        만약 AutoPtr헤더에 객체를 복사하는 생성자나 오퍼레이터에서
        a.m_ptr = nullptr; 와 같은 문장이 없었다면 결국 한 객체를 가리키는 포인터는 중복되서 생기게 된다.
        => 그렇다면 re1과 res2는 같은 객체를 가리키고 있을 때, res1이 먼저 지워지고 res2이 객체를 소멸시키고자 할 때 runtime exception이 발생할 수 있다.
        따라서 nullptr로 지정해줌으로써 객체를 완전히 이전하도록 하고, delete문을 실행하지 못하도록 한다.
        이를 move semantics라고 한다.
    */
    
}