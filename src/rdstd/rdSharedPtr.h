/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdSharedPtr.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*			
* ��  ��: liy ��������: 2014��5��23��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_SHAREDPTR_H_
#define _RD_SHAREDPTR_H_

#include <stdlib.h>
#include "rdstdtp.h"

BEGIN_RDSTD_NAMESPACE

/**
* @brief ����ָ����
*/
template <typename ElementType>
class RD_STD_DLL_ENTRY rdSharedPtr {
public:
    /**
     * @brief rdSharedPtr ���캯��
     */
    explicit rdSharedPtr(ElementType* ptr = NULL) : _pointer(ptr) {
        if (NULL != _pointer) {
            _pointer->inc();
        }
    }

    /**
     * @brief rdSharedPtr �������캯��
     */
    rdSharedPtr(const rdSharedPtr &other) : _pointer(other._pointer) {
        if (NULL != _pointer) {
            _pointer->inc();
        }
    }

    /**
     * @brief rdSharedPtr �������캯��
     *
     * @tparam U UΪrdSharedPtr������
     * @param other other����ElementType�������ָ��
     */
    template <typename U>
        rdSharedPtr(const rdSharedPtr<U> &other) : _pointer(NULL) {
            _pointer = other.get();
            if (NULL != _pointer) {
                _pointer->inc();
            }
        }

    /**
     * @brief ~rdSharedPtr ���캯����������ü�����Ϊ0�����ͷ���Դ
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
     * @brief operator= ��ֵ�����
     *
     * @param r ��ֵ������Ҳ�����
     */
    rdSharedPtr & operator=(const rdSharedPtr& r) {
        if(_pointer != r._pointer) { //�Ѿ��ж�(this != &r)
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
     * @brief get ��ȡ�ײ���Դָ��
     *
     * @return  �ײ���Դָ��
     */
    ElementType* get() const {
        return _pointer;
    }

    /**
     * @brief operator-> ���صײ���Դָ��
     *
     * @return ��Դָ��
     */
    ElementType* operator->() const {
        return _pointer;
    }

    /**
     * @brief operator ���صײ���Դ����
     *
     * @return ��Դ����
     */
    ElementType& operator*() const {
        return *_pointer;
    }

    /**
     * @brief is_valid �жϱ�����ָ���Ƿ���кϷ�����Դ
     *
     * @return ����true����ʾ�Ϸ������򣬷���false 
     */
    bool is_valid() const {
        return _pointer ? true : false;
    }

private:
    ElementType* _pointer;  /** �ײ���Դָ��*/
};
END_RDSTD_NAMESPACE
#endif 

