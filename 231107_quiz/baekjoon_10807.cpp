#include <iostream>

/*
    https://www.acmicpc.net/problem/10807
*/

int main() {
    int n;
    std::cin >> n;
    int nums[101];
    for(int i=0; i<n; i++) {
        std::cin >> nums[i];
    }

    int v;
    std::cin >> v;
    int count=0;
    for(int i=0; i<n; i++) {
        if(nums[i] == v) count++;
    }
    std::cout << count ;

}