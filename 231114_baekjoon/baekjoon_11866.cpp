#include <iostream>
#include <queue>

// https://www.acmicpc.net/problem/11866
int main() {
    int n, k;
    std::queue<int> circle;
    std::cin >> n;
    std::cin >> k;
    for(int i=0; i<n; i++) {
        circle.push(i+1);
    }

    int count=0;
    std::cout << "<";
    while(circle.size() > 1){
        count++;
        if(count%k == 0) {
            std::cout << circle.front() << ", ";
            circle.pop();
            continue;
        }
        circle.push(circle.front());
        circle.pop();
    }
    std::cout << circle.front() << ">";
}