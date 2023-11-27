#include <mysql/mysql.h>
#include <iostream>

int main() {
    MYSQL *conn;        // MySQL 연결 객체
    MYSQL_RES *res;     // MySQL 결과 객체
    MYSQL_ROW row;      // MySQL 결과에서 반환되는 행(row) 객체

    conn = mysql_init(NULL);  // MySQL 연결 객체 초기화

    // MySQL 연결 설정
    if (conn == NULL) {
        std::cerr << "mysql_init() failed" << std::endl;  // 초기화 실패 시 오류 출력
        return 1;  // 프로그램 종료
    }

    // MySQL 서버에 연결
    conn = mysql_real_connect(conn, "localhost", "adw", "123", "test", 0, NULL, 0);

    if (conn == NULL) {
        std::cerr << "mysql_real_connect() failed: " << mysql_error(conn) << std::endl;  // 연결 실패 시 오류 출력
        return 1;  // 프로그램 종료
    }

    // 쿼리 실행
    if (mysql_query(conn, "SELECT * FROM testTable")) {
        std::cerr << "mysql_query() failed" << std::endl;  // 쿼리 실행 실패 시 오류 출력
        return 1;  // 프로그램 종료
    }

    // 쿼리 결과를 메모리에 저장
    res = mysql_store_result(conn);

    if (res == NULL) {
        std::cerr << "mysql_store_result() failed" << std::endl;  // 결과 저장 실패 시 오류 출력
        return 1;  // 프로그램 종료
    }

    // 결과 출력
    while ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << "ID: " << row[0] << ", name: " << row[1] << ", addr: " << row[2] << std::endl;
    }

    // 메모리 해제
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
