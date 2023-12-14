#pragma once

#include <iostream>

class Resource {
// private:
public:
    int* m_data = nullptr;  // 규모가 큰 데이터를 다루기 위해 동적 array로 변경
    unsigned m_length = 0;
public:
    Resource(){ // 기본생성자
        std::cout << "Resource default constructed" << std::endl;
    }
    Resource(unsigned length) { // 숫자를 받는 기본생성자
        std::cout << "Resource length constructed" << std::endl;
        this->m_data = new int[length];
        this->m_length = length;
    }
    Resource(const Resource &res){  // 복사생성자
        std::cout << "Resource copy constructed" << std::endl;
        Resource(res.m_length);
        for(unsigned i=0; i<m_length; ++i) {
            m_data[i] = res.m_data[i];  // deep copy
        }
    }

    ~Resource(){    // 소멸자
        std::cout << "Resource destroyed" << std::endl;
        if(m_data != nullptr) delete[] m_data;
    }

    Resource& operator = (Resource &res){   // 복사 대입연산자
        std::cout << "Resource copy assginment" << std::endl;
        if(&res == this) return *this;  // 자신을 참조한 경우
        if(this->m_data != nullptr) delete[] m_data;

        m_length = res.m_length;
        m_data = new int[m_length];

        for(unsigned i=0; i<m_length; ++i) {
            m_data[i] = res.m_data[i];
        }
        return *this;
    }
};