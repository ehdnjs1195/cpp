#include <iostream>
// https://www.acmicpc.net/problem/10871
int main() {
    int n;
    int arr[10001];
    int x;

    std::cin >> n;
    std::cin >> x;
    for(int i=0; i<n; i++) {
        std::cin >> arr[i];
    }
    for(int i=0; i<n; i++) {
        if(arr[i] < x) {
            std::cout << arr[i] << " ";
        }
    }
}