#include <iostream>
#include <string>
#include <stack>

using namespace std;
int main() {
    string line;
    stack<char> ps, check;

    while(getline(cin,line)) {
        if(line.empty()) break;
        for(auto ch : line) {
            cout  << "ch: " << ch << endl;  //debuging
            if(!ps.empty() && ((ps.top() == '(' && ch == ')') || (ps.top() == '[' && ch == ']'))) {
                ps.pop();
                check.push(ch);
            } else if(line.size() == 1 && ch==' ') {
                check.push(ch);
                cout << "yes!!\n";
                continue;
            } else {
                ps.push(ch);
                check.push(ch);
            }
        }
        
        if(ps.empty()) cout << "yes\n";
        else cout << "no\n";
        
        for(int i=0; i<check.size(); i++) {
            cout << check.top();
            check.pop();
        cout << endl;
        }

    // for(int i=0; i<scripts.size(); i++) {
    //     cout << scripts.top() << endl;
    //     scripts.pop();
    // }
    }

}