#include <iostream>
#include <deque>

template<typename T>
void print_deque(std::deque<T>& container) {
    // ��ü ����ϱ�
    std::cout << "[ ";
    for(const auto& elem : container) {
        std::cout << elem << " ";
    }
    std::cout << " ]"<< std::endl;
}
void deque() {
    std::deque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(30);
    dq.push_front(40);

    std::cout << "�ʱ� dq ����" << std::endl;
    print_deque(dq);

    std::cout << "�� ���� ���� ����" <<std::endl;
    dq.pop_front();
    print_deque(dq);
}

int main(){
    deque();
}