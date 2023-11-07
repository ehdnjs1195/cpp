#include <iostream>

// https://www.acmicpc.net/problem/10810
int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    int i,j,k;
    int arr[n] = {0,};
    int count=0;
    while(count < m) {
        std::cin >> i;
        std::cin >> j;
        std::cin >> k;
        for(int x = i-1; x <j; x++) {
            arr[x] = k;
        }
        count++;
    }

    for(int i=0; i<n; i++) {
        std::cout << arr[i] << " ";
    }
    
}