#ifndef _PUBLIC_FASTSTR_H
#define _PUBLIC_FASTSTR_H

#include "CharTraits.h"
#include "common.h"

class TFastStrAlloc
{
    public:
        TFastStrAlloc(){}
        ~TFastStrAlloc(){}

        void *Alloc(size_t size){return new char[size];}
        void Free(void* ptr, size_t size){delete[] (char*)ptr;}
        void Swap(TFastStrAlloc& src){std::cout<<"TFastStrAlloc Swap"<<std::endl;}

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

        self_type& operator=(const self_type& src)
        {
            return inner_assign(src.c_str(), src.length());
        }

        TFastStr(const TYPE* src)
        {
            init(src, TRAITS::Length(src));
        }

        TFastStr(const self_type& src)
        {
            init(src.c_str(), src.length());
        }

        TFastStr(const TYPE* src, size_t len)
        {
            init(src, len);
        }

        TFastStr(const TYPE* s1, const TYPE* s2)
        {
            init2(s1, TRAITS::Length(s1), s2, TRAITS::Length(s2));
        }

        TFastStr(const TYPE* s1, size_t len1, const TYPE* s2, size_t len2)
        {
            init2(s1, len1, s2, len2);
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

        void swap(self_type& src)
        {
            std::cout<<"swap start "<<src.c_str()<<std::endl;
            size_t temp_size = src.m_nSize;
            size_t temp_capacity = src.m_nCapacity;
            TYPE* temp_pdata = src.m_pData;
            std::cout<<"temp_stack "<<(void*)src.m_Stack<<std::endl;
            TYPE temp_stack[SIZE];

            if(temp_capacity <= SIZE)
            {
                TRAITS::Copy(temp_stack, src.m_Stack, temp_size+1);
            }

            std::cout<<"m_nSize "<<m_nSize<<" m_nCapacity "<<m_nCapacity<<" "<<SIZE<<std::endl;
            //交换size和capacity
            src.m_nSize = m_nSize;
            src.m_nCapacity = m_nCapacity;

            if(m_nCapacity<=SIZE)
            {
                std::cout<<"src.m_Stack "<<(void*)src.m_Stack<<" m_Stack "<<(void*)m_Stack<<std::endl;
                //这里可以理解成被清空了
                TRAITS::Copy(src.m_Stack, m_Stack, m_nSize +1);
                src.m_pData = src.m_Stack;
            }
            else{
                std::cout<<"m_pData "<<(void*)m_pData<<std::endl;
                src.m_pData = m_pData;
            }

            m_nSize = temp_size;
            m_nCapacity = temp_capacity;

            if(temp_capacity <= SIZE)
            {
                TRAITS::Copy(m_Stack, temp_stack, temp_size+1);
                m_pData = m_Stack;
            }
            else{
                m_pData = temp_pdata;
            }

            m_Alloc.Swap(src.m_Alloc);
        }

        void showStack(TYPE* stack)
        {
            for(int i  =0;i<SIZE;i++)
            {
                std::cout<<(TYPE)*(stack+i);
            }
            std::cout<<std::endl;
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

        self_type& inner_assign(const TYPE* s, size_t len)
        {
            std::cout<<"inner assign start"<<std::endl;
            std::cout<<"len "<<len<<" cap "<<m_nCapacity<<std::endl;
            if(len<m_nCapacity)
            {
                TRAITS::Copy(m_pData, s, len);
                TRAITS::Put(m_pData+len, 0);
                m_nSize = len;
            }
            else{
                self_type temp(s, len);
                std::cout<<"temp "<<temp.length()<<" cap "<<temp.m_nCapacity<<std::endl;
                swap(temp);
                std::cout<<"show temp"<<std::endl;
                show(temp);
            }
            return *this;
        }

        self_type& inner_append(const TYPE* s, size_t len)
        {
            const size_t NEW_SIZE = m_nSize+len;
            if(NEW_SIZE < m_nCapacity)
            {
                TRAITS::Copy(m_pData + m_nSize, s, len);
                TRAITS::Put(m_pData + m_nSize + len, 0);
                m_nSize = NEW_SIZE;
            }
            else
            {
                self_type temp(c_str(), length(), s, len);
                swap(temp);
            }
            return *this;
        }

    private:
        ALLOC m_Alloc;
        TYPE m_Stack[SIZE];
        TYPE* m_pData;
        size_t m_nCapacity;
        size_t m_nSize;
};

#endif
