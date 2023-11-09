#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_container(T& c) {
    std::cout << "[ ";
    for(auto it = c.begin(); it != c.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << " ] " << std::endl;
}
template <typename T>
void print_container(std::set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    for (const auto& elem : s) {
        std::cout << elem << " " << std::endl;
    }
}

void ex1() {
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "순서대로 정렬되서 나온다." << std::endl;
    print_container(s);

    std::cout << "20이 s의 원소인가요? :: ";
    auto it = s.find(20);
    if (it != s.end()) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    std::cout << "25가 s의 원소인가요? :: " ;
    it = s.find(25);
    if (it != s.end()) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}


class Todo {
    int priority;
    std::string job_desc;
public:
    Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}
    
    /*
        반드시 이 꼴을 지켜주어야 함. operator<(const Todo& t), const {} 
        const Todo를 레퍼런스로 받는 const 함수로.
        이유는, set 내부적으로 정렬 시에 상수 반복자를 사용하기 때문이다. 
        => 상수 반복자는 상수 함수만을 호출할 수 있다.
    */
    bool operator<(const Todo& t) const {   // set은 원소들을 저장할 때 내부적으로 정렬된 상태를 유지하기 위해 반드시 비교를 수행해야 한다. 따라서 operator<를 정의해주어야 한다.
        if(priority == t.priority) {
            return job_desc < t.job_desc;
        }
        return priority > t.priority;
    }

    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};


std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[ 중요도: " << td.priority << "]" << td.job_desc;
    return o;
}



void ex2() {
    std::set<Todo> todos;

    todos.insert(Todo(1, "농구 하기"));
    todos.insert(Todo(2, "수학 숙제 하기"));
    todos.insert(Todo(1, "프로그래밍 프로젝트"));
    todos.insert(Todo(3, "친구 만나기"));
    todos.insert(Todo(2, "영화 보기"));
    
    print_container(todos);

    std::cout << "----------------" << std::endl;
    std::cout << "숙제를 끝냈다면!" << std::endl;
    todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
    print_container(todos);
}

int main() {
    // ex1();
    ex2();
}