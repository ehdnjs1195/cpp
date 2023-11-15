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
void u16string() {
    std::u16string u16_str = u"이건 UTF-16 문자열 입니다";
    std::cout << u16_str.size() << std::endl;
}
void u16string_jaum_print() {
    std::u16string u16_str = u"안녕하세용 모두에 코드에 오신 것을 환영합니다";
    std::string jaum[] = {"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
                            "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
                            "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"};

    for (char16_t c : u16_str) {
        // 유니코드 상에서 한글의 범위
        if (!(0xAC00 <= c && c <= 0xD7A3)) {
            continue;
        }
        // 한글은 AC00 부터 시작해서 한 초성당 총 0x24C 개 씩 있다.
        int offset = c - 0xAC00;
        int jaum_offset = offset / 0x24C;
        std::cout << jaum[jaum_offset];
    }
}
int main () {
    // u32string();
    // u8string();
    // print_char_u8string();
    // u16string();
    u16string_jaum_print();
}