#include "header1.h"
#include "header2.h"

namespace header1
{
    int func()
    {
        foo();  // header1 namespace 안에 속하므로 앞에 namespace 명시 없이 함수를 작성할 수 있음
        header2::foo();
    }
}