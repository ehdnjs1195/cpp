#include <iostream>
#include <set>
#include <string>

template <typename T, typename C>
void print_set(std::set<T,C>& s) {
    //셋의 모든 원소들을 출력하기
    for(const auto& elem : s) {
        std::cout << elem << " " << std::endl;
    }
}

class Todo {
    int priority;
    std::string job_desc;
public:
    Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}

    friend struct TodoCmp;

    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};
/*
    만일 외부라이브러리(이 예제의 경우 Todo 클래스)에서 operator< 가 오버로딩 되어 있지 않다면,
    해당 클래스에 대한 비교 연산을 정의해주어야 한다. 이를 위해 별도의 비교함수나 구조체를 만들어 사용하거나,
    함수 객체를 사용할 수 있다.
    아래는 함수객체를 comparator로 만들어 사용하는 예시이다.
*/
struct TodoCmp {
    bool operator() (const Todo& t1, const Todo& t2) const {    // 함수객체(Functor)를 이용해서 Todo객체를 비교함
        if(t1.priority == t2.priority) {
            return t1.job_desc < t2.job_desc;
        }
        return t1.priority > t2.priority;
    }
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[ 중요도: " << td.priority << "] " << td.job_desc;
    return o;
}


int main() {
    std::set<Todo, TodoCmp> todos;  //set<Todo>에 compare를 해주는 함수객체를 같이 넘겨주는 형태. 알아서 삽입, 삭제할 때 비교연산을 함.
    //삽입될 때는 TodoCmp의 operator()를 호출하여 트리를 순회하여 정렬된 위치를 찾아간다.
    todos.insert(Todo(1, "농구 하기"));
    todos.insert(Todo(2, "수학 숙제 하기"));
    todos.insert(Todo(1, "프로그래밍 프로젝트"));
    todos.insert(Todo(3, "친구 만나기"));
    todos.insert(Todo(2, "영화 보기"));

    print_set(todos);

    std::cout << "----------------" << std::endl;
    std::cout << "숙제를 끝냈다면!" << std::endl;
    todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
    print_set(todos);
}