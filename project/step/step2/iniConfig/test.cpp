#include <iostream>
#include "ConfigParser.hpp"

int main() {
    CConfigParser test("protocol.ini");
    if(test.IsSuccess()){
        // std::cout << test.GetInt("ID") << std::endl;

        // std::cout << test.GetInt("IntTest") << std::endl;
		// std::cout << test.GetBool("BoolTest") << std::endl;
		// std::cout << test.GetString("StringTest") << std::endl;
		// std::cout << test.GetFloat("FloatTest") << std::endl;
    }

    return 0;
}