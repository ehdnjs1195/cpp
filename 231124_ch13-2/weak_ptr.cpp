#include <iostream>
#include <memory>
#include <string>
#include <vector>

class A {
    std::string s;
    std::weak_ptr<A> other;

    public:
    A(const std::string& s) : s(s) { std::cout << "자원을 획득함!" << std::endl; }

    ~A() { std::cout << "소멸자 호출!" << std::endl; }

    void set_other(std::weak_ptr<A> o) { other = o; }
    void access_other() {
        std::shared_ptr<A> o = other.lock();
        if (o) {
            std::cout << "접근 : " << o->name() << std::endl;
        } else {
            std::cout << "이미 소멸됨 ㅠ" << std::endl;
        }
    }
    std::string name() { return s; }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;
    vec.push_back(std::make_shared<A>("자원 1"));
    vec.push_back(std::make_shared<A>("자원 2"));

    vec[0]->set_other(vec[1]);
    vec[1]->set_other(vec[0]);

    // pa 의와 pb  ref count 는 그대로다.
    std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

    // weak_ptr 로 해당 객체 접근하기
    vec[0]->access_other();

    // 벡터 마지막 원소 제거 (vec[1] 소멸)
    vec.pop_back();
    vec[0]->access_other();  // 접근 실패!
}