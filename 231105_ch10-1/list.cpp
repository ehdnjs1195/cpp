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

    std::cout << "ó�� ����Ʈ�� ����" << std::endl;

    for(std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        if(*itr == 20) {
            lst.insert(itr, 50);    //���� ���� ���Ұ� 20�̸� ���� �տ� 50�� �߰��Ѵ�.
        }
    }

    std::cout << "���� 20�� ���� �տ� 50 �߰�" << std::endl;
    print_list(lst);

    for(auto itr = lst.begin(); itr != lst.end(); ++itr) {
        if(*itr == 30) {
            lst.erase(itr); // ���� ���Ұ� 30�̸� �����ϱ�
            break;
        }
    }

    std::cout << "���� 30�� ���Ҹ� ����" << std::endl;
    print_list(lst);
}
int main()
{
    // list();
    list2();
}