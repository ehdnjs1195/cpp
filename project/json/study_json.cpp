#include <iostream>
#include <boost/json/src.hpp>   // json의 경우 헤더파일을 한번은 include 해주어야 한다.
// #include <boost/json.hpp>

/*
    참고 사이트
    1. boost 라이브러리(boost/json.hpp) 활용법:  https://www.boost.org/doc/libs/1_83_0/libs/json/doc/html/json/quick_look.html#json.quick_look.allocators
    2. nlohmann 라이브러리(nlohmann/json.hpp) 활용법(참고만): https://github.com/nlohmann/json#design-goals
*/

using namespace boost::json;

void json_object() {
    std::cout << "[ json_object() ]" << std::endl;

    object obj;                                                     // construct an empty object
    obj[ "pi" ] = 3.141;                                            // insert a double
    obj[ "happy" ] = true;                                          // insert a bool
    obj[ "name" ] = "Boost";                                        // insert a string
    obj[ "nothing" ] = nullptr;                                     // insert a null
    obj[ "answer" ].emplace_object()["everything"] = 42;            // insert an object with 1 element
    obj[ "list" ] = { 1, 0, 2 };                                    // insert an array with 3 elements
    obj[ "object" ] = { {"currency", "USD"}, {"value", 42.99} };    // insert an object with 2 elements

    std::cout << obj << std::endl;
}
void json_value(){
    std::cout << "[ json_value() ]" << std::endl;

    value jv = {
    { "pi", 3.141 },
    { "happy", true },
    { "name", "Boost" },
    { "nothing", nullptr },
    { "answer", {
        { "everything", 42 } } },
    {"list", {1, 0, 2}},
    {"object", {
        { "currency", "USD" },
        { "value", 42.99 }
            } }
    };

    std::cout << jv << std::endl;
    std::cout << "serialize(jv): " << serialize(jv) << std::endl;
}
void json_array(){
    std::cout << "[ json_array() ]" << std::endl;

    array arr;                                          // construct an empty array
    arr = { 1, 2, 3 };                                  // replace the contents with 3 elements
    std::cout << "arr: " << arr << std::endl;

    value jv1( arr );                                   // this makes a copy of the array
    std::cout << "jv1(arr): " << jv1 << std::endl;           // object, array, keys 등 생성하면서 복사.

    value jv2( std::move(arr) );                        // this performs a move-construction
    std::cout << "jv2(std::move(arr)): " << jv2 << std::endl;

    assert( arr.empty() );                              // moved-from arrays become empty
    std::cout << "arr.empty(): " << arr << std::endl;

    arr = { nullptr, true, "boost" };                   // fill in the array again
    std::cout << "arr: " << arr << std::endl;

}
void json_allocators(){
    std::cout << "[ json_allocators() ]" << std::endl;

    unsigned char buf[ 4096 ];                      // storage for our array
    static_resource mr( buf );                      // memory resource which uses buf
    array arr( &mr );                               // construct using the memory resource
    arr = { 1, 2, 3 };                              // all allocated memory comes from `buf`
    /*
        static_resource는 메모리 할당, 해제 전략을 사용자가 원하는대로 지정할 수 있도록 하는 클래스이다.
        - 주로 스택이나 정적 배열과 같은 고정된 메모리 영역에서 동적으로 메모리를 할당하고 관리하는데 사용된다.
    */
}
void json_serialization() {
    std::cout << "[ json_serialization() ]" << std::endl;

    value jv = {1,2,3};
    std::string s = serialize(jv);
    /*
        Serialization(직렬화) 
            - 데이터를 바이트 스트림 또는 다른 형태로 변환 하는 과정 
                => json에서 직렬화는 데이터 구조를 json 형식의 문자열로 변환하는 것.
            - 일반적으로 프로그램이나 데이터를 저장하거나 네트워크를 통해 전송할 때 사용된다.
            - deserialization(역직렬화)하여 원래의 데이터 구조를 복원할 수 있다.
            - serialize.ipp => ipp는 인라인 함수 정의에 사용함.
    */
    std::cout << "jv: " << jv << std::endl;
    std::cout << "s: " << s << std::endl;
}
void json_parsing() {
    std::cout << "[ json_parsing() ]" << std::endl;

    value jv = parse( "[1, 2, 3]" );
    std::cout << "jv: " << jv << std::endl;

    error_code ec;
    value jv2 = parse( R"( "Hello, world!" )", ec );    // 파싱이 성공하면 jv에는 파싱된 JSON 값이 저장되고, 실패하면 ec에는 해당 오류 코드가 저장됩니다. 
    std::cout << "jv2(ec): " << jv2 << " || ec: " << ec <<std::endl;    // ec를 확인하여 파싱이 성공적으로 수행되었는지, 그리고 어떤 종류의 오류가 발생했는지 알 수 있습니다.
}
void json_parsing_opt() {
    unsigned char buf[ 4096 ];
    static_resource mr( buf );
    parse_options opt;
    opt.allow_comments = true;  // 기본적으로 JSON 파서는 주석을 허용하지 않습니다. 이 옵션을 설정하면 JSON 문서 내에서 주석을 허용하게 됩니다.
    opt.allow_trailing_commas = true;
    value jv = parse( "[1, 2, 3, ] // array ", &mr, opt );  //  JSON 표준은 배열 또는 객체의 마지막 요소 뒤에 쉼표를 허용하지 않습니다. 이 옵션을 설정하면 마지막 요소 뒤에 쉼표를 허용합니다.
    // mr에 의해 메모리 할당, 해제가 제어된다. 이때 value의 jv가 mr에의해 메모리가 동적할당 되는 것이다.
    std::cout << jv << std::endl;
}
void json_stream_parser() {
    stream_parser p;
    error_code ec;
    p.reset();
    p.write( "[1, 2 ", ec );
    if( ! ec )
        p.write( ", 3]", ec );
    if( ! ec )
        p.finish( ec );
    if( ec )
        return;
    value jv = p.release();
    /*
        stream parser는 JSON을 스트리밍 방식으로 처리하는 예제입니다.
        스트리밍 방식은 전체 입력이 처음부터 사용 가능할 필요 없이 JSON을 조각조각 처리할 수 있는 방식을 의미합니다. 
    */
    std::cout << "jv: " << jv << " || ec: " << ec << std::endl;
}
int main() {
    // json_object();
    // json_value();
    // json_array();
    // json_allocators();
    // json_serialization();
    // json_parsing();
    // json_parsing_opt();
    json_stream_parser();
    return 0;
}
