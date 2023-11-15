#include <iostream>
#include <string>

struct Queue{   // queue 구현하기
int* queue;
int length;

Queue():length(0){
        queue = new int[10000];
}
    void push(int x) {
        queue[length] = x;
        length++;
    }
    void pop() {
        if(queue[0] != '\0'){
            std::cout << queue[0] << std::endl;
            for(int i=0; i<length; i++) {
                queue[i] = queue[i+1];
            }
            queue[length-1] == '\0';
            length--;
        } else {
            std::cout << -1 << std::endl;
        }
    }
    void size() {
        std::cout << length << std::endl;
    }
    void empty() {
        if(queue[0] == '\0') {
            std::cout << 1 << std::endl;
            return;
        }
        std::cout << 0 << std::endl;
        return;
    }
    void front() {
        if(queue[0] != '\0') {
            std::cout << queue[0] << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }
    void back() {
        if(queue[0] != '\0') {
            std::cout << queue[length-1] << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }
};

int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(NULL);

    Queue q;
    int n;
    std::cin >> n;

    while(n--) {
        std::string command;
        std::cin >> command;
        if(command == "push") {
            int x;
            std::cin >> x;
            q.push(x);
        } else if (command == "pop") {
            q.pop();
        } else if (command == "size") {
            q.size();
        } else if (command == "empty") {
            q.empty();
        } else if (command == "front") {
            q.front();
        } else if (command == "back") {
            q.back();
        }
    }
}