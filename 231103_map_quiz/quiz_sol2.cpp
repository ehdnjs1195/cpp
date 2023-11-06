#include <iostream>
#include <string>
#include <map>
#include <vector>
/*
    https://www.acmicpc.net/problem/1764
    
*/
int main() 
{
    int n, m;
    std::cin >> n;
    std::cin >> m;
    std::map<std::string, int> result;
    std::vector<std::string> answer;

    std::string tmp;
    for(int i=0; i<n+m; i++) {
        std::cin >> tmp;
        result[tmp]++;
    }
    int count = 0;
    for(auto it : result) {
        if(it.second == 2) {
            answer.push_back(it.first);
        }
    }

    std::cout << answer.size() << std::endl;
    for(auto r:answer) {
        std::cout << r << std::endl;
    }

    return 0;
}