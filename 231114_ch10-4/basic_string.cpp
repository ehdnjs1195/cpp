#include <cctype>
#include <iostream>
#include <string>

// char_traits 의 모든 함수들은 static 함수 입니다.
struct my_char_traits : public std::char_traits<char> {
  static int get_real_rank(char c) {
    // 숫자면 순위를 엄청 떨어트린다.
    if (isdigit(c)) {
      return c + 256;
    }
    return c;
  }

  static bool lt(char c1, char c2) {    // 문자들간의 크기를 비교하는 함수 오버로딩
    return get_real_rank(c1) < get_real_rank(c2);
  }

  static int compare(const char* s1, const char* s2, size_t n) {    // 길이 n의 문자열 크기 비교하는 함수 오버로딩
    while (n-- != 0) {
      if (get_real_rank(*s1) < get_real_rank(*s2)) {
        return -1;
      }
      if (get_real_rank(*s1) > get_real_rank(*s2)) {
        return 1;
      }
      ++s1;
      ++s2;
    }
    return 0;
  }
};

int main() {
  std::basic_string<char, my_char_traits> my_s1 = "1a"; //숫자보다 문자의 순위가 높도록 정의한 basic_string타입
  std::basic_string<char, my_char_traits> my_s2 = "a1";

  std::cout << "숫자의 우선순위가 더 낮은 문자열 : " << std::boolalpha
            << (my_s1 < my_s2) << std::endl;

  std::string s1 = "1a";    // 일반 string에서는 숫자가 문자보다 순위가 더 높다.
  std::string s2 = "a1";

  std::cout << "일반 문자열 : " << std::boolalpha << (s1 < s2) << std::endl;
}