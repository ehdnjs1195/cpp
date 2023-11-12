#include <iostream>
#include <set>
#include <string>

template <typename K>
void print_set(const std::multiset<K>& s) {
    // 셋의 모든 원소들을 출력하기
    for (const auto& elem : s) {
        std::cout << elem << std::endl;
    }
}

int main() {
    std::multiset<std::string> s;

    s.insert("a");
    s.insert("b");
    s.insert("a");
    s.insert("c");
    s.insert("d");
    s.insert("c");

    print_set(s);
}