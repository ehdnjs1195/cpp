#include <iostream>
#include <queue>

//https://www.acmicpc.net/problem/2164

int main() {
    int n;
    std::queue<int> deck;

    std::cin >> n;
    for(int i=0; i<n; i++) {
        deck.push(i+1);
    }

    while(deck.size() > 1) {
        deck.pop();
        deck.push(deck.front());
        deck.pop();
    }
    std::cout << deck.front() ;
}