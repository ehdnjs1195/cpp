#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <initializer_list>
template <typename T>
void print_vec(const std::vector<T> &vec)
{
    std::cout << "[";
    for (const auto &e : vec)
    {
        std::cout << e << " ";
    }
    std::cout << "]" << std::endl;
}

template <typename K, typename V>
void print_map(const std::map<K, V> &m)
{
    for (const auto &kv : m)
    {
        std::cout << kv.first << " : " << kv.second << std::endl;
    }
}

/*
    initializer_list의 주의할 점.
    - {} 를 이용해서 객체를 생성할 경우 생성자 오버로딩 시에 해당 함수가 최우선 으로 고려된다는 점
    - 컴파일러가 최선을 다해서 해당 생성자와 매칭시키려고 노력한다는 의미
    - 따라서 벡터와 같이 초기화를 할 때 vector v(10); 와 vector v{10}를 주의해서 사용할 것.
*/
class A
{
public:
    A(int x, double y) { std::cout << "일반 생성자! " << std::endl; }

    A(std::initializer_list<int> lst)   // 최우선시 고려된다!
    {
        std::cout << "초기화자 사용 생성자! " << std::endl;
    }
};

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    print_vec(v);

    std::cout << "----------------------" << std::endl;
    std::map<std::string, int> m = {
        {"abc", 1}, {"hi", 3}, {"hello", 5}, {"c++", 2}, {"java", 6}};
    print_map(m);


    // 주의할 점
    A a(3, 1.5);  // Good
    // A b{3, 1.5};  // Bad! initializer_list가 최우선으로 고려되기 때문에, 암시적 형변환이 불가능하므로 1.5에서 컴파일 오류가 발생함.
}