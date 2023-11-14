#include <iostream>
#include <stack>

//https://www.acmicpc.net/problem/10773

int main() {
    int k, n;
    std::stack<int> result;
    std::cin >> k;
    for(int i=0; i<k; i++) {
        std::cin >> n;
        if(n != 0) {
            result.push(n);
        } else {
            result.pop();
        }
    }
    int sum = 0;
    int result_size = result.size();
    for(int i=0; i<result_size; i++) {
        sum += result.top();
        result.pop();   // pop을 하고나면 result.size()가 줄어들어서 반복문이 다 돌지 못함. 변수 따로 선언
    }
    std::cout << sum << std::endl;
}

