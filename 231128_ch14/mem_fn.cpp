#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using std::vector;

void error_code() {
    vector<int> a(1);
    vector<int> b(2);
    vector<int> c(3);
    vector<int> d(4);

    vector<vector<int>> container;
    container.push_back(b);
    container.push_back(d);
    container.push_back(a);
    container.push_back(c);

    vector<int> size_vec(4);
    // transform : 각 원소들에 대해 인자로 전달된 함수를 실행시킨 다음 결과를 전달된 컨테이너에 넣어준다.
    // std::transform(container.begin(), container.end(), size_vec.begin(), &vector<int>::size);    
    // 문제는 transform 전달 받는 unary_op 인자가 멤버함수일 경우이다.
    /*  
        [짚고 넘어갈 개념!]
        멤버 함수 포인터는 클래스의 멤버 함수를 가리키는 포인터로서, 일반 함수 포인터와는 사용 방법이 다릅니다.

        여기서 unary_op는 멤버 함수인 vector<int>::size를 가리키는 포인터입니다. 
        일반적인 함수 포인터 호출은 함수포인터(인자) 형태로 이루어집니다. 
        그러나 멤버 함수 포인터는 객체가 필요한데, 그 객체는 멤버 함수를 호출할 때 암묵적으로 전달됩니다.

        그래서 멤버 함수를 호출할 때, 객체.*(멤버함수포인터)와 같은 문법을 사용합니다. 
        그러나 transform 함수가 일반 함수 포인터를 가정하고 있어서 문제가 발생하는 것입니다.

        해결책은 std::function을 사용하여 람다 함수를 전달하는 것입니다. 
    */
    for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
        std::cout << "벡터 크기 :: " << *itr << std::endl;
    }
}
void correct_code(){
    vector<int> a(1);
    vector<int> b(2);
    vector<int> c(3);
    vector<int> d(4);

    vector<vector<int>> container;
    container.push_back(a);
    container.push_back(b);
    container.push_back(c);
    container.push_back(d);

    std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
    // 하지만 매번 function 객체를 만들어서 전달하는 것은 매우 귀찮음. => function 객체를 리턴해버리는 함수가 생김.
    vector<int> size_vec(4);
    std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);
    for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
        std::cout << "벡터 크기 :: " << *itr << std::endl;
    }  
}
void mem_fn_code() {    // 개선.
    vector<int> a(1);
    vector<int> b(2);
    vector<int> c(3);
    vector<int> d(4);

    vector<vector<int>> container;
    container.push_back(a);
    container.push_back(b);
    container.push_back(c);
    container.push_back(d);

    vector<int> size_vec(4);
    transform(container.begin(), container.end(), size_vec.begin(),
                std::mem_fn(&vector<int>::size));   // size함수를 전달
    for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
        std::cout << "벡터 크기 :: " << *itr << std::endl;
    }
    /*
        람다 함수로도 동일한 작업을 수행할 수 있다.
        mem_fn(&vector<int>::size) 대신에
        [](const auto& v){ return v.size()} 를 전달
    */
}
int main() {
    // error_code();
    // correct_code();
    mem_fn_code();
}