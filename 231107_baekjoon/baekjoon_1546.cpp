#include <iostream>

// https://www.acmicpc.net/problem/1546
int main() {
    int n;
    int max = 0;
    int max_idx=0;
    std::cin >> n;

    double arr[n];
    for(int i=0; i<n; i++) {
        std::cin >> arr[i];
        if(arr[i] > max) {
            max = arr[i];
            max_idx = i;
        }
    }

    // 출력은 double형이어야 하므로 sum의 자료형 주의
    double sum=0;
    for(int i=0; i<n; i++){
        sum += arr[i] / max*100;
    }

    std::cout <<  sum/n ;
}