#include <iostream>
#include <string>
#include <stack>

using namespace std;
void sol_by_iingang(){
    ios::sync_with_stdio(0);
	cin.tie(0);

	while(true){
		stack<char> S;
		string str;
		
		getline(cin, str);
		
		if(str==".")
			break;
	
		bool flag = true;
			
		for(int i=0; i<str.size(); i++){
			
			if(str[i] == '[' || str[i] == '('){
				S.push(str[i]);
			}
			
			else if(str[i] == ']'){
				if(S.empty()){
					flag = false;
					break;
				}
				
				else if(S.top() == '['){
					S.pop();
				}
				
				else if(S.top() == '('){
					flag = false;
					break;
				}
			}
			
			else if(str[i] == ')'){
				if(S.empty()){
					flag = false;
					break;
				}
				
				else if(S.top() == '('){
					S.pop();
				}
				
				else if(S.top() == '['){
					flag = false;
					break;
				}
			}
			
		}
		
		if(S.empty() && flag)
			cout << "yes\n" ;
			
		else
			cout << "no\n" ;
	
	}
}

int main() {
    ios::sync_with_stdio(0);
	cin.tie(0);
    
    string line;
    stack<char> ps;

    while(getline(cin,line)) {
        if(line.at(0) == '.') break;    // 종료 조건
        // cout << "line: " << line << endl;
        for(auto ch : line) {
            if (ch == '(' || ch == '[') {
                ps.push(ch);
            } else if(!ps.empty() && ((ps.top() == '(' && ch == ')') || (ps.top() == '[' && ch == ']'))) {
                ps.pop();
            } 
        }
        
        if (ps.empty()) cout << "yes\n";
        else cout << "no\n";
        
        while (!ps.empty()) {   // 차있는 스택 비우기.
            ps.pop();
        }
    }

}