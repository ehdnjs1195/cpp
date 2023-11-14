#include <iostream>
#include <string>



void u32string() {
    std::u32string u32_str = U"이건 UTF-32 문자열 입니다";  //실제 문자열 길이 17
    std::cout << u32_str.size() << std::endl;
}
void u8string() {
    std::string str = u8"이건 UTF-8 문자열 입니다"; // 실제 문자열 길이 16 이지만, 한글은 3byte, 나머지(공백포함) 1byte 로 계산하면 32byte가 된다.=> 32개 char
    std::cout << str.size() << std::endl;
}
void print_char_u8string() {
    std::string str = u8"이건 UTF-8 문자열 입니다";
    size_t i=0;
    size_t len=0;

    while(i < str.size()) {
        int char_size = 0;
        if((str[i] & 0b11111000) == 0b11110000) char_size = 4;
        else if((str[i] & 0b11110000) == 0b11100000) char_size = 3;
        else if((str[i] & 0b11100000) == 0b11000000) char_size = 2;
        else if((str[i] & 0b10000000) == 0b00000000) char_size = 1;
        else {
            std::cout << "이상한 문자 발견" << std::endl;
            char_size = 1;
        }
        std::cout << str.substr(i,char_size) << std::endl;
        
        i += char_size;
        len++;
    }
    std::cout << "문자열 실제 길이는 : "  << len << std::endl;
}
int main () {
    // u32string();
    // u8string();
    print_char_u8string();
}