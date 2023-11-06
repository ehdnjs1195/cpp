#include <iostream>

// 재귀 호출 종료를 위한 베이스 케이스
int sum_all() { return 0; }
// 베이스 케이스는 파라미터 팩이 없는 함수가 우선순위가 높기 때문에 파라미터팩으로 전달될 인자가 없다면 먼저 호출된다. => 따라서 필요함.
template <typename... Ints>
int sum_all(int num, Ints... nums)
{
    return num + sum_all(nums...);
}

template <typename... Ints>
double average(Ints... nums)
{
    return static_cast<double>(sum_all(nums...)) / sizeof...(nums); 
    // sizeof... 에 파라미터 팩 (nums) 를 전달하면 nums 에 해당하는 실제 인자의 개수를 리턴해줍니다. 
}
/*
    ## static_cast<새로운_데이터_타입>(표현식)
        - 현재 예제에서는 double 타입으로 형 변환 하고있음.
    ## sizeof...은 C++11 이후에 추가된 C++ 템플릿 메타프로그래밍의 일부로
        가변인자 템플릿을 사용할 때 인자 팩에 속한 인자의 개수를 구하는데 사용된다.
        - sizeof...(nums)는 nums 팩에 전달된 인자의 개수를 반환.
*/
int main()
{
    // (1 + 4 + 2 + 3 + 10) / 5
    std::cout << average(1, 4, 2, 3, 10) << std::endl;
}