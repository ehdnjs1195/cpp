#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
    for(auto itr = m.begin(); itr != m.end(); ++itr) {
        // 반복자가 맵에 저장되어 있는 std::pair 객체를 가리키게 된다. 따라서 ->를 사용해 키, 값을 참조한다.
        std::cout << itr->first << " " << itr->second << std::endl; 
    }
}

template <typename K, typename V>
void print_map2(std::map<K, V>& m) {
    // kv에는 맵의 key, value가 std::pair로 들어간다.
    for(const auto& kv : m ) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}

int main() {
    std::map<std::string, double> pitcher_list;\

    //맵의 insert 함수는 pair 객체를 인자로 받습니다.
    pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
    pitcher_list.insert(std::pair<std::string, double>("해커", 2.93));
    pitcher_list.insert(std::pair<std::string, double>("피어밴드", 2.95));

    // 타입을 지정하지 않아도 간단히 std::make_pair함수로 std::pair 객체를 만들 수 있다.
    pitcher_list.insert(std::make_pair("차우찬", 3.04));
    pitcher_list.insert(std::make_pair("장원준", 3.05));
    pitcher_list.insert(std::make_pair("헥터", 3.09));

    // [] 로 바로 원소를 추가할 수 있다.
    pitcher_list["니퍼트"] = 3.56;
    pitcher_list["박종훈"] = 3.76;  
    pitcher_list["켈리"] = 3.90;

    print_map2(pitcher_list);

    std::cout << "박세웅의 방어율은? :: " << pitcher_list["박세웅"] << std::endl;  
}