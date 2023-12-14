#include "AutoPtr.hpp"
#include "Resource.hpp"
#include "Timer.hpp"
AutoPtr<Resource> generateResource()
{
    AutoPtr<Resource> res(new Resource(10000000));

    return res;
}

int main()
{
    using namespace std;
    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL); //disconnect cout from buffer  => cout을 못하게 끊어주는 것
    
    Timer timer;

    {
        AutoPtr<Resource> main_res;
        main_res = generateResource();
    }

    cout.rdbuf(orig_buf);   // cout은 시간이 오래걸리는 작업임. 이것을 제어하는 문장.
    timer.elapsed();

    return 0;
}