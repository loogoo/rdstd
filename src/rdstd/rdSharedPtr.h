/***************************************************************************
* 版权信息: Copyright (C) 2014 mr.li版权所有
* 文件名称: rdSharedPtr.h 
* 当前版本: 1.0
* 摘  要:
*			
* 作  者: liy 创建日期: 2014年5月23日
* 修改记录: 
***************************************************************************/
#ifndef _RD_SHAREDPTR_H_
#define _RD_SHAREDPTR_H_

#include <stdlib.h>
#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

/**
* @brief 智能指针类
*/
template <typename ElementType>
class RD_STD_DLL_ENTRY rdSharedPtr {
public:
    /**
     * @brief rdSharedPtr 构造函数
     */
    explicit rdSharedPtr(ElementType* ptr = NULL) : _pointer(ptr) {
        if (NULL != _pointer) {
            _pointer->inc();
        }
    }

    /**
     * @brief rdSharedPtr 拷贝构造函数
     */
    rdSharedPtr(const rdSharedPtr &other) : _pointer(other._pointer) {
        if (NULL != _pointer) {
            _pointer->inc();
        }
    }

    /**
     * @brief rdSharedPtr 拷贝构造函数
     *
     * @tparam U U为rdSharedPtr子类型
     * @param other other持有ElementType派生类的指针
     */
    template <typename U>
        rdSharedPtr(const rdSharedPtr<U> &other) : _pointer(NULL) {
            _pointer = other.get();
            if (NULL != _pointer) {
                _pointer->inc();
            }
        }

    /**
     * @brief ~rdSharedPtr 构造函数，如果引用计数减为0，则释放资源
     */
    ~rdSharedPtr() {
        if (NULL != _pointer) {
            if (_pointer->dec() == 0) {
                delete _pointer;
                _pointer = NULL;
            }
        }
    }

    /**
     * @brief operator= 赋值运算符
     *
     * @param r 赋值运算符右操作数
     */
    rdSharedPtr & operator=(const rdSharedPtr& r) {
        if(_pointer != r._pointer) { //已经判断(this != &r)
            if (NULL != r._pointer) {
                r._pointer->inc();
            }

            ElementType *ptr = _pointer;
            _pointer = r._pointer;
            if (NULL != ptr) {
                if(ptr->dec() == 0){
                    delete ptr;
                    ptr = NULL;
                }
            }
        }

        return *this;
    }

    /**
     * @brief get 获取底层资源指针
     *
     * @return  底层资源指针
     */
    ElementType* get() const {
        return _pointer;
    }

    /**
     * @brief operator-> 返回底层资源指针
     *
     * @return 资源指针
     */
    ElementType* operator->() const {
        return _pointer;
    }

    /**
     * @brief operator 返回底层资源引用
     *
     * @return 资源引用
     */
    ElementType& operator*() const {
        return *_pointer;
    }

    /**
     * @brief is_valid 判断本智能指针是否持有合法的资源
     *
     * @return 返回true，表示合法；否则，返回false 
     */
    bool is_valid() const {
        return _pointer ? true : false;
    }

private:
    ElementType* _pointer;  /** 底层资源指针*/
};
END_RDSTD_NAMESPACE
#endif 

