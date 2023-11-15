#include <iostream>
#include <stack>

using namespace std;
int main() {
    int n;
    stack<int> wait, pass;

    cin >> n;
    for(int i=0; i<n; i++) {    // 대기순번 받기
        int temp;
        cin >> temp;
        
        if(wait.empty() && temp == n) { // 처음에 숫자가 마지막 숫자일 경우
            wait.push(temp);
        } else if(pass.empty() && temp == 1) {  // 처음에 숫자가 1일 경우
            pass.push(temp);
        } else if(!wait.empty() && temp == wait.top() - 1) {    
            wait.push(temp);
        } else if(!pass.empty() && temp == pass.top() + 1) {
            pass.push(temp);
        }
    }

    if((wait.size() + pass.size()) == n) {
        cout << "Nice\n";
    } else {
        cout << "Sad\n";
    }

}
