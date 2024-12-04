
class Array
{
    const int dim;  // 차원의 개수
    int* size;      // 각 차원의 크기

    struct Address
    {
        int level;  // 현재의 차원(1,2,3.. 차원)
        void* next; // 다음 차원의 배열을 가리키는 포인터(재귀적 구조)
    };

    Address* top;

public:
    /* 재귀적 구조로 만들어지는 배열임을 생각할 것 */
    Array(int dim, int* array_size) : dim(dim)  // 값 대입 ex) dim = 3, array_size = {4,3,1} => 이때 dim의 숫자는 array_size 크기와 같아야함.
    {
        size = new int[dim];    // N차원: 각 차원의 크기
        for(int i = 0; i < dim; i++) size[i] = array_size[i];   // N차원의 i일 때 배열의 크기를 복사하는 과정
    };

    // address 를 초기화 하는 함수이다. 재귀 호출로 구성되어 있다.
    void initialize_address(Address *current) {
    if (!current) return;
        if (current->level == dim - 1)  // 두 번째 질문 (종료 조건) => 즉, 마지막 차원(최하위 차원)은 실제 값이 들어가는 int배열
        {
            current->next = new int[size[current->level]];
            return;
        }
        current->next = new Address[size[current->level]]; // 그 중간 차원은 Address 구조체의 배열을 할당한다
        for (int i = 0; i != size[current->level]; i++)
        {   // 다음 단계로 넘어가는 과정
            (static_cast<Address *>(current->next) + i)->level = current->level + 1;

            initialize_address(static_cast<Address *>(current->next) + i);
        }
    }

    void delete_address(Address *current)
    {
        if (!current) return;
        for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++) {
            delete_address(static_cast<Address *>(current->next) + i);
        }

        if (current->level == dim - 1) {    // 최하위 차원일 때는
            delete[] static_cast<int *>(current->next); // int배열을 해제
        }

        delete[] static_cast<Address *>(current->next); // 중간 차원에서 Address배열을 해제함
    }

    void copy_address(Address *dst, Address *src) {
        if (dst->level == dim - 1) {
            for (int i = 0; i < size[dst->level]; ++i)
            static_cast<int *>(dst->next)[i] = static_cast<int *>(src->next)[i];
            return;
        }
        for (int i = 0; i != size[dst->level]; i++) {
            Address *new_dst = static_cast<Address *>(dst->next) + i;
            Address *new_src = static_cast<Address *>(src->next) + i;
            copy_address(new_dst, new_src);
        }
    }


    ~Array() {
        delete_address(top);
        delete[] size;
    }
};