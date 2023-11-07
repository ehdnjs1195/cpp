#include <iostream>
#include <set>

// https://www.acmicpc.net/problem/3052
int main() {
    int n=10;
    std::set<int> nums;

    for(int i=0; i<n; i++) {
        int temp;
        std::cin >> temp;
        nums.insert(temp % 42);
    }
    std::cout << nums.size();
}