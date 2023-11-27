#include <iostream>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

int main() {
    SQLHENV henv;
    SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    // ODBC 버전 설정
    ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // DB 연결 핸들 생성
    SQLHDBC hdbc;
    ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

    // 연결 문자열 생성
    SQLWCHAR* connectionString = (SQLWCHAR*)L"DRIVER=mysql;SERVER=127.0.0.1;DATABASE=test;UID=adw;PWD=123;";

    // DB에 연결
    ret = SQLDriverConnectW(hdbc, NULL, connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    // 쿼리 실행을 위한 문장 핸들 생성
    SQLHSTMT hstmt;
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    // SQL문 실행
    SQLWCHAR* sql = (SQLWCHAR*)L"SELECT * FROM testTable";
    ret = SQLExecDirectW(hstmt, sql, SQL_NTS);

    // 결과 가져오기
    if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLWCHAR name[50];
        SQLINTEGER age;
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            SQLGetData(hstmt, 1, SQL_C_WCHAR, name, 50, NULL);
            SQLGetData(hstmt, 2, SQL_C_LONG, &age, sizeof(age), NULL);  // 변수 이름 및 타입 수정

            // 결과 출력
            wcout << L"name: " << name << L", age: " << age << endl;
        }
    }

    SQLDisconnect(hdbc);
    // 핸들 해제
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);

    return 0;
}