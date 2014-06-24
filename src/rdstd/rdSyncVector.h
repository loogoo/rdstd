/***************************************************************************
* ��Ȩ��Ϣ: Copyright (C) 2014 mr.li��Ȩ����
* �ļ�����: rdSyncVector.h 
* ��ǰ�汾: 1.0
* ժ  Ҫ:
*
*			�̰߳�ȫvector
*			
* ��  ��: liy ��������: 2014��5��24��
* �޸ļ�¼: 
***************************************************************************/
#ifndef _RD_SYNCVECTOR_H_
#define _RD_SYNCVECTOR_H_

#include <vector>
#include "rdMutex.h"
#include "rdSemaphore.h"

#include "rdError.h"
#include "rdShared.h"


BEGIN_RDSTD_NAMESPACE

template <typename ElemType>
class RD_STD_DLL_ENTRY rdSyncVector : public rdShared {
public:
    rdSyncVector() { }
    typedef rdGuard<rdMutex> ScopedGuard;

    /**
     * @brief put ��ͬ��vector�����Ԫ�أ������ظ�����ͬʱ�����ź���
     *
     * @param elem ��Ԫ��
     *
     * @return ��ӳɹ�����0�����򷵻ش�����
     */
    int32_t put(ElemType elem) {
        {
            ScopedGuard guard(&_mutex);
            if (guard.is_locked()) {
                try {
                    _vector.push_back(elem);
                }
                catch(std::bad_alloc &) {
                    return E_NOMEM;
                }
            }
            else {
                return E_SYSERROR;
            }
        }
        _sem.signal();
        return 0;
    }

    /**
     * @brief get ��ͬ��vector��ȡԪ�ء����ͬ��vectorΪ�գ�������ָ��ʱ��WAIT_INFINITE��ʾ����������
     *
     * @param elem ȡ�õ�Ԫ��
     * @param millisecond ��ʱʱ�������룩
     *
     * @return �ɹ�����0�����򷵻ش�����: E_TIMEOUT��ʾ��ʱ.
     */
    int32_t get(ElemType& elem, int millisecond) {
        int32_t ret = _sem.wait(millisecond);

        if (0 == ret) {
            {
                ScopedGuard guard(&_mutex);
                if (guard.is_locked()) {
                    elem = _vector.back();
                    _vector.pop_back();
                }
                else {
                    return E_SYSERROR;
                }
            }
            return 0;
        }
        else {
            return ret;
        }
    }

    int32_t size() {
        ScopedGuard guard(&_mutex);
        return (int32_t)_vector.size();
    }

protected:
    rdSyncVector(const rdSyncVector&);
    rdSyncVector& operator=(const rdSyncVector&);

private:
    std::vector<ElemType> _vector;
    rdMutex _mutex;
    rdSemaphore _sem;

}; // end of class rdSyncVector


END_RDSTD_NAMESPACE

#endif
