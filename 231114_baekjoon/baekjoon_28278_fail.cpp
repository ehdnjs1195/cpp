#include <iostream>
#include <vector>

// https://www.acmicpc.net/problem/28278

struct Stack {
    std::vector<int> stack;
    
    void command_1(int x) {
        stack.push_back(x);
    }
    void command_2() {
        if(!stack.empty()) {
            std::cout << stack.back() << std::endl;            
            stack.pop_back();
        } else {
            std::cout << -1 << std::endl;
        }
    }
    void command_3() {
        std::cout << stack.size() << std::endl;
    }
    void command_4() {
        if(stack.empty()) {
            std::cout << 1 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    void command_5() {
        if(!stack.empty()) {
            int tmp = stack.back();
            std::cout << tmp << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    Stack stack;
    int n;
    std::cin >> n;
    while (n--) {
        int command;
        std::cin >> command;
        switch (command)
        {
            case 1:
                int tmp;
                std::cin >> tmp;
                stack.command_1(tmp);
                break;
            case 2:
                stack.command_2();
                break;
            case 3:
                stack.command_3();
                break;
            case 4:
                stack.command_4();
                break;
            case 5:
                stack.command_5();
                break;
            default:
                break;
        }
    }
}
