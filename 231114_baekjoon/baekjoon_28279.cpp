#include <iostream>
#include <deque>


// https://www.acmicpc.net/problem/28279

using namespace std;
int main() {
    cin.tie(0); 
	cout.tie(0); 
	ios::sync_with_stdio(false);

    int n, command, x;
    deque<int> d;
    cin >> n;

    while(n--) {
        cin >> command;
        switch(command) {
            case 1:
                cin >> x;
                d.push_front(x);
                break;
            case 2:
                cin >> x;
                d.push_back(x);
                break;
            case 3:
                if(!d.empty()) {
                    cout << d.front() << "\n";
                    d.pop_front();
                } else {
                    cout << -1 << "\n";
                }
                break;
            case 4:
                if(!d.empty()) {
                    cout << d.back() << "\n";
                    d.pop_back();
                } else {
                    cout << -1 << "\n";
                }
                break;
            case 5:
                cout << d.size() << "\n";
                break;
            case 6:
                if(d.empty()) {
                    cout << 1 << "\n";
                } else {
                    cout << 0 << "\n";
                }
                break;
            case 7:
                if(!d.empty()) {
                    cout << d.front() << "\n";
                } else {
                    cout << -1 << "\n";
                }
                break;
            case 8:
                if(!d.empty()) {
                    cout << d.back() << "\n";
                } else {
                    cout << -1 << "\n";
                }
                break;
            default:
                break;
        }
    }

}