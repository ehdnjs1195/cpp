#include <iostream>

/* 나만의 std::array 구현 */

#include <iostream>

template <typename T, unsigned int N>
class Array {
    T data[N];

public:
// 배열을 받는 레퍼런스 arr
    Array(T (&arr)[N]) {        // &arr은 arr 배열을 참조로 전달받는 것을 나타냅니다. 이것은 배열을 복사하지 않고 직접 참조로 전달하여 효율적으로 작업할 수 있게 합니다.
                                // 배열 arr에 대한 참조로, 배열의 크기 N과 원소 타입 T를 명시적으로 지정합니다.
        for (int i = 0; i < N; i++) {
            data[i] = arr[i];   // data에 복사
        }
    }

    T* get_array() { return data; } // data 배열에 대한 포인터를 반환합니다. 이 함수를 사용하면 배열 내의 데이터에 직접 액세스할 수 있습니다.

    unsigned int size() { return N; }

    void print_all() {
        for (int i = 0; i < N; i++) {
            std::cout << data[i] << ", ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int arr[3] = {1, 2, 3};

    // 배열 wrapper 클래스
    Array<int, 3> arr_w(arr);

    arr_w.print_all();
}