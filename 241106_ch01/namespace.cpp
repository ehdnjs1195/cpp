#include "header1.h"
#include "header2.h"

namespace header1
{
    int func()
    {
        foo();
        header2::foo();
    }
}