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
    AutoPtr(const AutoPtr &a)   // l-value reference
    {
        std::cout << "AutoPtr copy constructor" << std::endl;

        // deep copy
        m_ptr = new T;
        *m_ptr = *a.m_ptr; // 이부분에서 모든 걸 다 deep copy를 하기 때문에 속도가 느려질 것이다.
    }
    AutoPtr& operator=(const AutoPtr &a)
    {
        std::cout << "AutoPtr copy assginment" << std::endl;

        if (&a == this)
            return *this; // 자기 자신객체를 넣을경우

        if(m_ptr != nullptr) delete m_ptr;

        // deep copy
        m_ptr = new T;
        *m_ptr = *a.m_ptr;  // 이부분에서 모든 걸 다 deep copy를 하기 때문에 속도가 느려질 것이다.

        return *this;
    }

    T &operator*() const { return *m_ptr; }; // dereferencing (역참조)
    T *operator->() const { return m_ptr; }; // member slicing?
    bool isNull() const { return m_ptr == nullptr; };
};