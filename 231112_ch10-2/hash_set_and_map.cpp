#include <iostream>
#include <functional>
#include <string>
#include <unordered_set>

template <typename K>
void print_unordered_set(const std::unordered_set<K>& s) {
    for(const auto& elem : s) {
        std::cout << elem << std::endl;
    }
}

template <typename K>
void is_exist(std::unordered_set<K>& s, K key) {
    auto itr = s.find(key);
    if (itr != s.end()) {
        std::cout << key << " 가 존재!" << std::endl;
    } else {
        std::cout << key << " 가 없다" << std::endl;
    }
}
class Todo {
    int priority;  // 중요도. 높을 수록 급한것!
    std::string job_desc;

 public:
    Todo(int priority, std::string job_desc)
        : priority(priority), job_desc(job_desc) {}

    bool operator==(const Todo& t) const {
        if (priority == t.priority && job_desc == t.job_desc) return true;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& o, const Todo& t);
    friend struct std::hash<Todo>;
};
/*
    Todo 해시 함수를 위한 함수객체(Functor)를 만들어줍니다!

    이 특수화의 목적은 Todo 클래스에 대한 사용자 정의 해시 함수를 제공하여 해당 형식의 객체를 
    std::unordered_set과 같은 무순서 연관 컨테이너의 키로 사용할 수 있게 하는 것입니다.
*/
namespace std {
template <>
struct hash<Todo> {
    size_t operator()(const Todo& t) const {
        hash<string> hash_func; // 기본 타입에 대한 해시함수를 제공하기 때문에 이를 이용하여 만들자!

        return t.priority ^ (hash_func(t.job_desc));
    }
};
}  // namespace std
std::ostream& operator<<(std::ostream& o, const Todo& t) {
    o << "[중요도 : " << t.priority << " ] " << t.job_desc;
    return o;
}

int main() {
    std::unordered_set<Todo> todos;

    todos.insert(Todo(1, "농구 하기"));
    todos.insert(Todo(2, "수학 숙제 하기"));
    todos.insert(Todo(1, "프로그래밍 프로젝트"));
    todos.insert(Todo(3, "친구 만나기"));
    todos.insert(Todo(2, "영화 보기"));
    print_unordered_set(todos);
    std::cout << "----------------" << std::endl;
}