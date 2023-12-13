#include <iostream>
int getResult(){return 10*10;};
int main() {
    int x = 3;
    const int cx = 6;

    // ### L-value references에 대하여
    int &lr1 = x;       // Modifiable l-value
    // int &lr2 = cx;   // Non-modifiable l-value
    // int &lr3 = 5;    // R-value

    const int &lr4 = x; // Modifiable l-value
    const int &lr5 = cx;// Non-modifiable l-value
    const int &lr6 = 5; // R-value                 => 여기서 가능한 이유: 메모리 주소와 상관없이 이후에 수정을 안할 것이기 때문에. 마치 symbolic constant(기호상수)와 같이 쓰겠다.

    // ### R-value references에 대하여
    /*
        r-value reference 만 가질 수 있음.
        - 사라질 값이지만 임시로 보관해줄 수 있다는 것. 
        - move semantics 를 사용할 때 l-value와 r-value의 차이가 있음.

    */
    // int &&rr1 = x;           // Modifiable l-value
    // int &&rr2 = cx;          // Non-modifiable l-value
    int &&rr3 = 5;              // R-value  => 사라질 값이지만 임시로 보관해줄 수 있다는 것. 
    int &&rrr = getResult();

    // 헷갈릴 수 있는 점.
    std::cout << rr3 << std::endl;
    rr3 = 10;   // 없어질 값이라더니 값을 바꿀 수가 있어??
    std::cout << rr3 << std::endl;

    // const int &&rr4 = x;     // Modifiable l-value
    // const int &&rr5 = cx;    // Non-modifiable l-value
    const int &&rr6 = 5;        // R-value                

    
}