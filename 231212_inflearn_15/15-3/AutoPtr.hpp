#pragma once
#include <iostream>

template <class T>
class AutoPtr
{
public:
    T *m_ptr;

public:
    AutoPtr(T *ptr = nullptr)
        : m_ptr(ptr)
    {
        std::cout << "AutoPtr default constructor" << std::endl;
    }
    ~AutoPtr()
    {
        std::cout << "AutoPtr destructor" << std::endl;
        if (m_ptr != nullptr)
            delete m_ptr;
    }

    // ###복사 생성자, 복사 할당 연산자 파트
    // AutoPtr(const AutoPtr &a)   // l-value reference
    // {
    //     std::cout << "AutoPtr copy constructor" << std::endl;

    //     // deep copy
    //     m_ptr = new T;
    //     *m_ptr = *a.m_ptr; // 이부분에서 모든 걸 다 deep copy를 하기 때문에 속도가 느려질 것이다.
    // }
    // AutoPtr& operator=(const AutoPtr &a)
    // {
    //     std::cout << "AutoPtr copy assginment" << std::endl;

    //     if (&a == this)
    //         return *this; // 자기 자신객체를 넣을경우

    //     if(m_ptr != nullptr) delete m_ptr;

    //     // deep copy
    //     m_ptr = new T;
    //     *m_ptr = *a.m_ptr;  // 이부분에서 모든 걸 다 deep copy를 하기 때문에 속도가 느려질 것이다.

    //     return *this;
    // }

    // AutoPtr(const AutoPtr& a) = delete;
    // AutoPtr& operator=(const AutoPtr& a) = delete;

    // ###이동 생성자, 이동 할당 연산자 파트
    AutoPtr(AutoPtr&& a) 
        : m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;  // 소유권을 m_ptr로 넘겨주고 nullptr로 변경. => 소멸자에서 nullptr는 지우지 않게 되있으므로 메모리를 지우지 않게됨.

        std::cout << "AutoPtr move constructor " << std::endl;
    }

    AutoPtr& operator=(AutoPtr&& a)
    {
        std::cout << "AutoPtr move assignment" << std::endl;

        if(&a == this)  // prevent self-assignment
            return *this;
        
        if(!m_ptr) delete m_ptr;

        // shallow copy
        m_ptr = a.m_ptr;    // 메모리의 첫 주소 하나만 넘겨주는 것.
        a.m_ptr = nullptr;  // 그리고 널포인터로 변경

        return *this;
    }


    T &operator*() const { return *m_ptr; }; // dereferencing (역참조)
    T *operator->() const { return m_ptr; }; // member slicing?
    bool isNull() const { return m_ptr == nullptr; };
};