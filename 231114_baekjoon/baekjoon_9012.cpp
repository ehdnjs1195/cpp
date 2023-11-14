#include <iostream>
#include <vector>
#include <string>
#include <stack>

//https://www.acmicpc.net/problem/9012

using namespace std;
void sol_by_jooooooon() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int N;
    cin >> N;
    while (N--) {
        string input;
        cin >> input;
        stack<char> stk;
        for (auto c : input) {
        if (!stk.empty() && stk.top() == '(' && c == ')')
            stk.pop();
        else
            stk.push(c);
        }
        string ans = stk.empty() ? "YES" : "NO";
        cout << ans << '\n';
    }

}

int main() {
    int n;
    int result=0; // 결과
    std::vector<std::string> ps;
    
    std::cin >> n;
    
    for(int i=0; i<n; i++) {
        std::string tmp;
        std::cin >> tmp;
        ps.push_back(tmp);
    }

    for(auto str : ps) {
        for(int i=0; str.size(); i++){
            char tmp = str.back();
            if(tmp == '(') {
                result--;
            }
            else if(tmp == ')') {
                result++;
            }

            if(result < 0) {    // 뒤에서 삭제하는데 0보다 작다는 것은 이미 괄호가 올바르지 않다는 뜻.
                std::cout << "NO\n";
                str.clear();
                break;
            }
            str.pop_back();
        }

        if(result == 0) {
            std::cout << "YES\n";
        } else if(result > 0) {
            std::cout << "NO\n";
        }
        result =0;
    }
}

