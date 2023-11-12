#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
    for(const auto& kv : m) {   
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}
/*
    내가 헷갈리지 말 것 한가지. 
    1. 범위기반 for문에서 auto는 std::pair<K, V> 자체를 나타낸다.
    for(const auto& kv : m) {   
        std::cout << kv.first << " " << kv.second << std::endl;
    }
        따라서 .으로 값에 접근해야 한다.
    2. iterator는 포인터와 같다고 생각해도 된다.
    for (auto itr = m.begin(); itr != m.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }
        여기서의 auto 는 std::map<K,V>::iterator 이다. 
        따라서 -> 로 값을 참조할 수 있다.

*/
//[] 사용시 주의할 점.
void ex1() {
    /*
        []연산자를 사용할 때 주의점!
        - 값을 넣지 않은 키값을 참조하는데 0이 출력되었다.
        - [] 연산자가, 맵에 없는 키를 참조하게 되면, 자동으로 값의 디폴트 생성자를 호출해서 원소를 추가해버리기 때문이다.
        - double 의 디폴트 생성자의 경우 그냥 변수를 0 으로 초기화 해버린다.

        => 따라서 되도록이면 find 함수로 원소의 키가 존재하는지 먼저 확인 후에, 값을 참조하는 것이 좋다.
    */
    std::map<std::string, double> pitcher_list;

    pitcher_list["오승환"] = 3.58;
    std::cout << "류현진의 방어율은? :: " << pitcher_list["류현진"] << std::endl;

    std::cout << "------------------" << std::endl;
    print_map(pitcher_list);
}
//find함수를 사용한 예
template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
    auto itr = m.find(key);
    if(itr != m.end()) {
        std::cout << key << " --> " << itr->second << std::endl;
    } else {
        std::cout << key << "은(는) 목록에 없습니다." << std::endl;
    }
}
void ex2() {
    std::map<std::string, double> pitcher_list;

    pitcher_list["오승환"] = 3.58;

    print_map(pitcher_list);
    std::cout << "-----------------" << std::endl;

    search_and_print(pitcher_list, std::string("오승환"));
    search_and_print(pitcher_list, std::string("류현진"));
}

int main() {
    // ex1();
    ex2();
}