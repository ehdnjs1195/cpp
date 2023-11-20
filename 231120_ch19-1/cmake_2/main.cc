#include "bar.h"
#include "foo.h"

int main() {
    foo();
    bar();
}

/*
    $ g++ -c main.cc => main.cc를 컴파일 하라는 뜻.
    - 목적 파일(object file)이 생성됨.

    g++ 에 전달하는 `-c` 명령어는 인자 다음에 주어지는 파일을 컴파일해서 목적파일(object file) 을 생성하라는 의미

    - 실제 프로그램에서는 각각의 파일들이 컴파일 되어서 main 하나에서 실행될 수 있도록 합치는 과정이 필요함(링킹).

    => make는 이러한 일련의 과정을 자동으로 해주는 것이다.
        - 주어진 쉘 명령어들을 조건에 맞게 실행하는 프로그램.
*/