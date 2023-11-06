#include <iostream>
#include <vector>

template<typename T>
void print_vector(std::vector<T>& vec) {
    //벡터 전체 출력하기
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

    std::cout << "처음 벡터 상태" << std::endl;
    print_vector(vec);
    std::cout << "----------------------------" << std::endl;

    // vec[2] 앞에 15 추가
    vec.insert(vec.begin() + 2, 15);
    print_vector(vec);

    std::cout << "----------------------------" << std::endl;
    // vec[3]제거
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

    std::cout << "처음 벡터 상태 " << std::endl;
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

    std::cout << "값이 20 인 원소를 지운다!" << std::endl;
    print_vector(vec);

    std::cout << vec.size() << ":" << vec.capacity() << std::endl;
}
void const_iterator(){
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "초기 vec 상태" << std::endl;
    print_vector(vec);

    std::vector<int>::iterator itr = vec.begin() + 2;

    *itr = 20;

    std::cout << "-------------" << std::endl;
    print_vector(vec);

    std::vector<int>::const_iterator citr = vec.cbegin() + 2;
    // *citr = 30;  // 상수 반복자가 가리키는 값은 바꿀 수 없다! 불가능.
}
void reverse_iterator(){
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    std::cout << "초기 vec 상태" << std::endl;
    print_vector(vec);

    std::cout << "역으로  vec  출력하기" << std::endl;
    
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

    // 끝에서 부터 출력하기 => i--를 하면 0보다 작은 정수로 가기 때문에 해당 타입의 가장 큰 정수가 되어버린다. 
    // 따라서 무한 반복이 되어 오류로 종료된다.
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