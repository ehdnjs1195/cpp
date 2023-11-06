#include <iostream>
#include <vector>

template<typename T>
void print_vector(std::vector<T>& vec) {
    //���� ��ü ����ϱ�
    for(typename std::vector<T>::iterator itr=vec.begin(); itr != vec.end(); ++itr) {
        std::cout << *itr << std::endl;
    }
}
void iterator1(){
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "ó�� ���� ����" << std::endl;
    print_vector(vec);
    std::cout << "----------------------------" << std::endl;

    // vec[2] �տ� 15 �߰�
    vec.insert(vec.begin() + 2, 15);
    print_vector(vec);

    std::cout << "----------------------------" << std::endl;
    // vec[3]����
    vec.erase(vec.begin() + 3);
    print_vector(vec);
}
void iterator2() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(20);

    std::cout << "ó�� ���� ���� " << std::endl;
    print_vector(vec);

    std::vector<int>::iterator itr = vec.begin();
    auto end_itr = vec.end();

    std::cout << vec.size() << ":" << vec.capacity() << std::endl;
    
    for(std::vector<int>::size_type i=0; i != vec.size(); i++) {
        if(vec[i] == 20) {
            vec.erase(vec.begin() + i);
            i--;
        }
    }

    std::cout << "���� 20 �� ���Ҹ� �����!" << std::endl;
    print_vector(vec);

    std::cout << vec.size() << ":" << vec.capacity() << std::endl;
}
void const_iterator(){
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "�ʱ� vec ����" << std::endl;
    print_vector(vec);

    std::vector<int>::iterator itr = vec.begin() + 2;

    *itr = 20;

    std::cout << "-------------" << std::endl;
    print_vector(vec);

    std::vector<int>::const_iterator citr = vec.cbegin() + 2;
    // *citr = 30;  // ��� �ݺ��ڰ� ����Ű�� ���� �ٲ� �� ����! �Ұ���.
}
void reverse_iterator(){
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "�ʱ� vec ����" << std::endl;
    print_vector(vec);

    std::cout << "������  vec  ����ϱ�" << std::endl;
    
    std::vector<int>::reverse_iterator r_itr = vec.rbegin();
    for(; r_itr != vec.rend(); r_itr++){
        std::cout << *r_itr << std::endl;
    }

}
void const_reverse_iterator(){
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // ������ ���� ����ϱ� => i--�� �ϸ� 0���� ���� ������ ���� ������ �ش� Ÿ���� ���� ū ������ �Ǿ������. 
    // ���� ���� �ݺ��� �Ǿ� ������ ����ȴ�.
    for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--) {
        std::cout << vec[i] << std::endl;
    }

}
template<typename T> 
void print_vector_range_based(std::vector<T>& vec) {
    for(const auto& elem : vec) {
        std::cout << elem << std::endl;
    }
}
void range_base_for() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "print_vector" << std::endl;
    print_vector(vec);
    std::cout << "print_vector_range_based" << std::endl;
    print_vector_range_based(vec);

}

int main(){
    // iterator1();
    // iterator2();
    // const_iterator();
    // reverse_iterator();
    // const_reverse_iterator();
    range_base_for();
    return 0;
}