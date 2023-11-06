#include <iostream>
#include <map>
#include <string>

int main() {
	std::map<std::string, std::string> m;
	m["seoul"] = "02";
	m["kyungki"] = "031";
	m["daegu"] = "051";
	m["incheon"] = "032";
	
	for (auto iter : m) {
		std::cout << iter.first << "의 지역번호:" << iter.second << std::endl;
	}
	std::cout << std::endl;

	std::cout <<"seoul:"<< m["seoul"] << std::endl;

	m["daegu"] = "053";
	std::cout << "daegu:" << m["daegu"] << std::endl;

}