#ifndef _PUBLIC_FASTSTR_H
#define _PUBLIC_FASTSTR_H

#include "CharTraits.h"

class TFastStrAlloc
{
    public:
        TFastStrAlloc(){}
        ~TFastStrAlloc(){}

        void *Alloc(size_t size){return new char[size];}
        void Free(void* ptr, size_t size){delete[] (char*)ptr;}
        void Swap(TFastStrAlloc& src){}

};

template<typename TYPE, size_t SIZE, typename TRAITS = TCharTraits<TYPE>,
    typename ALLOC = TFastStrAlloc>
class TFastStr
{
    private:
        typedef TFastStr<TYPE, SIZE, TRAITS, ALLOC> self_type;

    public:
        TFastStr()
        {
            m_Stack[0] = 0;
            m_pData = m_Stack;
            m_nCapacity = SIZE;
            m_nSize = 0;
        }

        ~TFastStr()
        {
            if(m_nCapacity > SIZE)
            {
                m_Alloc.Free(m_pData, m_nCapacity*sizeof(TYPE));
            }
        }

        TFastStr(const TYPE* src)
        {
            init(src, TRAITS::Length(src));
        }

        TFastStr(const self_type& src)
        {
            init(src.c_str(), src.length());
        }

        bool empty() const{
            return  (0==m_nSize);
        }

        size_t length() const{
            return m_nSize;
        }

        size_t size() const{
            return m_nSize;
        }

        size_t capacity() const{
            return m_nCapacity;
        }

        void clear(){
            if(m_pData != m_Stack)
            {
                m_Alloc.Free(m_pData, m_nCapacity*sizeof(TYPE));
            }
            m_Stack[0] = 0;
            m_pData = m_Stack;
            m_nCapacity = SIZE;
            m_nSize = 0;
        }

        const TYPE* c_str() const{
            return m_pData;
        }

    private:
        void init(const TYPE* src, size_t len)
        {
            m_nSize = len;

            if(m_nSize < SIZE)
            {
                m_nCapacity = SIZE;
                m_pData = m_Stack;
            }
            else
            {
                m_nCapacity = (m_nSize + 1)*2;
                m_pData = (TYPE*)m_Alloc.Alloc(m_nCapacity*sizeof(TYPE));
            }

            TRAITS::Copy(m_pData, src, m_nSize);
            TRAITS::Put(m_pData+m_nSize, 0);
        }

        void init2(const TYPE* s1, size_t SIZE1, const TYPE* s2, size_t SIZE2)
        {
            m_nSize = SIZE1+SIZE2;
            if(m_nSize<SIZE)
            {
                m_nCapacity = SIZE;
                m_pData = m_Stack;
            }
            else
            {
                m_nCapacity = (m_nSize+1)*2;
                m_pData = (TYPE*)m_Alloc.Alloc(m_nCapacity*sizeof(TYPE));
            }

            TRAITS::Copy(m_pData, s1, SIZE1);
            TRAITS::Copy(m_pData + SIZE1, s2, SIZE2);
            TRAITS::Put(m_pData+SIZE1+SIZE2, 0);
        }

    private:
        ALLOC m_Alloc;
        TYPE m_Stack[SIZE];
        TYPE* m_pData;
        size_t m_nCapacity;
        size_t m_nSize;
};

#endif
