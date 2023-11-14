#include <iostream>

// https://www.acmicpc.net/problem/10813
int main() {
    int n, m;
    int i,j;
    std::cin >> n;
    std::cin >> m;
    int arr[n];
    for(int k=0; k<n; k++) {
        arr[k] = k + 1;
    }

    for(int k=0; k<m; k++) {
        std::cin >> i;
        std::cin >> j;
        int tmp = arr[i-1];
        arr[i-1] = arr[j-1];
        arr[j-1] = tmp;
    }

    for(int x: arr) {
        std::cout << x << " ";
    }

}