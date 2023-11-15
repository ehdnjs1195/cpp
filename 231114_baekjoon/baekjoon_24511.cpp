#include <iostream>
#include <deque>


//https://www.acmicpc.net/problem/24511
using namespace std;

int main() {
    // ios::sync_with_stdio(0);
	// cin.tie(0);
    int n, m;
    deque<int> container;
    bool type[100001];

    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> type[i];
    }
    for(int i=0; i<n; i++) {
        int num;
        cin >> num;
        if(type[i]) continue;   // 사실상 stack은 배열에 영향을 미치지 않기 때문에 건너뛴다.
        container.push_back(num);   // queue일 때만 배열에 삽입
    }

    cin >> m;
    for(int i=0; i<m; i++) {
        int num;
        cin >> num;
        container.push_front(num);
        cout << container.back() << " ";
        container.pop_back();
    }
}