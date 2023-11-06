#include <iostream>
#include <list>

template<typename T>
void print_list(std::list<T>& list) {
    for(const auto& elem : list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
void list() {
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);

    for(std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        std::cout << *itr << std::endl;
    }
}
void list2(){
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);

    std::cout << "처음 리스트의 상태" << std::endl;

    for(std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        if(*itr == 20) {
            lst.insert(itr, 50);    //만약 현재 원소가 20이면 원소 앞에 50을 추가한다.
        }
    }

    std::cout << "값이 20인 원소 앞에 50 추가" << std::endl;
    print_list(lst);

    for(auto itr = lst.begin(); itr != lst.end(); ++itr) {
        if(*itr == 30) {
            lst.erase(itr); // 현재 원소가 30이면 삭제하기
            break;
        }
    }

    std::cout << "값이 30인 원소를 제거" << std::endl;
    print_list(lst);
}
int main()
{
    // list();
    list2();
}