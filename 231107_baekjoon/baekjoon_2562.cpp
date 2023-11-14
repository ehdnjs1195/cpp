#include <iostream>

// https://www.acmicpc.net/problem/2562
int main() {
    int arr[9];
    int max = 0;
    int count =0;
    for (int i=0; i<9; i++) {
        std::cin >> arr[i];
        if(arr[i] > max) {
            max = arr[i];
            count = i+1;
        }
    }
    std::cout << max << std::endl;
    std::cout << count << std::endl;
}

