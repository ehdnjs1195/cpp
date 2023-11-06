#include <iostream>
#include <array>

template  <typename T, int num>
T add_num(T t) {
    return t + num;
}
void ex1() {
    int x = 3;
    std::cout << "x: " << add_num<int, 5>(x) << std::endl;
}
void ex2() {
    // 마치 C 에서의 배열 처럼 {} 을 통해 배열을 정의할 수 있다.
    // {} 문법은 16 - 1 강에서 자세히 다루므로 여기서는 그냥 이렇게
    // 쓰면 되는구나 하고 이해하고 넘어가면 됩니다.
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    // int arr[5] = {1, 2, 3, 4, 5}; 와 동일

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl; 
}
void print_array(const std::array<int, 5>& arr) {   // 이미 타입과 크기가 정해진 배열이므로, std::array<int, 5> 자체가 하나의 타입으로 간주된다.
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void ex3() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    print_array(arr);
}
// 배열의 크기마다 함수를 생성할 수 없으므로 템플릿으로 구현
template <typename T>
void print_array(const T& arr) {
    for(int i=0; i<arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
void ex4() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    std::array<int, 7> arr2 = {1, 2, 3, 4, 5, 6, 7};
    std::array<int, 3> arr3 = {1, 2, 3};

    print_array(arr);
    print_array(arr2);
    print_array(arr3);
}
int main() {
    //ex1();
    // ex2();
    // ex3();
    ex4();
}