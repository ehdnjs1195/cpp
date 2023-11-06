#include <iostream>
#include <map>
#include <string>

void find_number(std::map<std::string, std::string> m, std::string key) {
    auto it = m.find(key);
    if(it != m.end()){
        std::cout << "키가 존재함" << std::endl;
    } else {
        std::cout << "키가 존재하지 않음" << std::endl;
    }
}

int main()
{
    std::map<std::string, std::string> users;
    users.insert(std::make_pair("010-1133-0000", "a"));
    users.insert(std::make_pair("010-1234-0000", "b"));
    users.insert(std::make_pair("010-2345-0000", "c"));
    users.insert(std::make_pair("010-3456-0000", "d"));
    // 2.
    find_number(users, "010-1133-0001");
    // 3-1.
    // users.erase("010-1133-0000");
    // 3-2. 첫번째방법
    // users.erase(users.begin(), users.end());
    // 3-2. 두번째방법
    // users.clear();
    // 4.
    std::cout << users.size() << std::endl;

    for(auto iter : users){
        std::cout << "name:" << iter.second << " phone:" << iter.first << std::endl;
    }

    
    return 0;
}
