#include <iostream>
#include <map>
#include <string>

template<typename T, typename N>
void print_container(std::map<T,N> map) {
    for(auto it=map.begin(); it != map.end(); it++) {
        std::cout << it[]
    }
}
int main(){
    std::map<int, std::string> map;
    map[0]="1번";
    map[1]="2번";


}