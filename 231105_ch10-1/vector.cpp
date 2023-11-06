#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    for (std::vector<int>::size_type i = 0; i < vec.size(); i++) {
        std::cout << "vec 의 " << i + 1 << " 번째 원소 :: " << vec[i] << std::endl;
    }
}