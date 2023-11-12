#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(const std::multimap<K, V>& m) {
    // 맵의 모든 원소들을 출력하기
    for (const auto& kv : m) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}

int main() {
    std::multimap<int, std::string> m;
    m.insert(std::make_pair(1, "hello"));
    m.insert(std::make_pair(1, "hi"));
    m.insert(std::make_pair(1, "ahihi"));
    m.insert(std::make_pair(2, "bye"));
    m.insert(std::make_pair(2, "baba"));

    print_map(m);

    std::cout << "--------------------" << std::endl;

    // equal_range함수는 1 을 키로 가지는 반복자들의 시작과 끝을
    // std::pair 로 만들어서 리턴한다.
    auto range = m.equal_range(1);
    for (auto itr = range.first; itr != range.second; ++itr) {  // range의 first는 반복자의 begin(), second는 end() 와 같은 역할을 한다. (즉, 마지막 원소의 뒷 자리를 가리킴.)
        std::cout << itr->first << " : " << itr->second << " " << std::endl;
    }
}