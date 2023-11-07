#include <iostream>

// https://www.acmicpc.net/problem/10811
int main() {
    int n, m;
    std::cin >> n >> m;
    int arr[n];
    for(int k=0; k<n; k++) {
        arr[k] = k+1;
    }

    int i,j;
    for(int k=0; k<m; k++) {
        std::cin >> i >> j;
        for(int x = i; x <= (i+j)/2; x++) {
            int tmp = arr[i-1];
            arr[i-1] = arr[j-1];
            arr[j-1] = tmp;
            i++;
            j--;
        }
    }

    for(int x: arr) {
        std::cout << x << " ";
    }
}