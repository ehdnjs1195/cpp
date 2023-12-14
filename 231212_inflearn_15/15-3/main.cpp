#include "AutoPtr.hpp"
#include "Resource.hpp"
#include "time.h"
AutoPtr<Resource> generateResource()
{
    AutoPtr<Resource> res(new Resource(10000000));

    return res;
}

int main()
{
    using namespace std;
    streambuf* orig_buf = cout.rdbuf();
    // cout.rdbuf(NULL); //disconnect cout from buffer  => cout을 못하게 끊어주는 것

    // Timer timer;

    {
        AutoPtr<Resource> main_res;
        main_res = generateResource();
    }

    cout.rdbuf(orig_buf);
    cout << timer.elapsed() << endl;
}