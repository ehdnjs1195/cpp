#pragma once
#include <iostream>
// smart pointer 구현해보기. 객체가 사라지면 자동으로 리소스를 해제해줌.
template <class T>
class AutoPtr {
public:
    T *m_ptr = nullptr;
public:
    AutoPtr(T *ptr = nullptr):m_ptr(ptr){

    }
    ~AutoPtr(){
        if(m_ptr != nullptr) delete m_ptr;
    }
    AutoPtr(AutoPtr &a) {   // 복사인데, 소유권을 넘겨주는 이동복사
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;  // nullptr가 되면 delete도 할 수 없게되어서 소유권을 완전히 넘긴다고 할 수 있음
    }
    AutoPtr& operator = (AutoPtr &a) {
        if(&a == this) return *this;    // 자기 자신객체를 넣을경우
        
        delete m_ptr;   // 원래 포인터를 삭제
        m_ptr = a.m_ptr;// 복사할 객체 주소로 바꾸기
        a.m_ptr = nullptr;// 소유권 완전히 넘겨주기
        return *this;
    }

    T& operator*() const {return *m_ptr;};  //dereferencing (역참조)
    T* operator->() const {return m_ptr;};  //member slicing?
    bool isNull() const {return m_ptr == nullptr;};
};