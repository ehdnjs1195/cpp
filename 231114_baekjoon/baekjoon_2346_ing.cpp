#include <iostream>
#include <deque>

using namespace std;

void t() {
    int n, s, k;
    deque<int> balls;
    int seq[n];

    cin >> n;
    for(int i=0; i<n; i++) {
        balls.push_back(i+1);
        int s;
        cin >> s;
        seq[i] = s;
    }

    while(n--) {
        s = balls.front();
        cout << s << " ";
        k = seq[s-1];
        if(k > 0) {
            balls.pop_front();
            while(--k > 0) {
                balls.push_back(balls.front());
                balls.pop_front();
            }
        } else if(k < 0) {
            balls.pop_front();
            while(k++ <= 0) {
                balls.push_front(balls.back());
                balls.pop_back();
            }
        }
    }
}
int main() {
    t();
}