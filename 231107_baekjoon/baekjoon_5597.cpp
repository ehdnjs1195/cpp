#include <iostream>

// https://www.acmicpc.net/problem/5597
int main() {
    int num = 30;
    int students[30] = {0, };
    for(int i=0; i<28; i++) {
        int called_num;
        std::cin >> called_num;
        students[called_num-1] = 1;
    }

    for(int i=0; i<num; i++){
        if(students[i] == 0) {
            std::cout << i+1 << std::endl;
        }
    }
}