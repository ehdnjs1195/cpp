#include <iostream>

// https://www.acmicpc.net/problem/10818
int main() {
    int n;
    int arr[1000001];
    std::cin >> n;

    int min=1000001;
    int max=-1000001;
    for(int i=0; i<n; i++) {
        std::cin >> arr[i];
        if(arr[i] > max) max = arr[i];
        if(arr[i] < min) min = arr[i];
    }

    std::cout << min << " " << max ;
}