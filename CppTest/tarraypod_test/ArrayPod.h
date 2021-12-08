#ifndef _TT_ARRAYPOD_H
#define _TT_ARRAYPOD_H

#include <string.h>
#include <stdlib.h>

class TArrayPodAlloc
{
	public:
		TArrayPodAlloc(){}
		~TArrayPodAlloc(){}

		void *Alloc(size_t size) { return (void *)new char[size]; }
		void Free(void *ptr, size_t size) { delete[](char *) ptr; }
		void Swarp(TArrayPodAlloc &src) {}
};

class TArrayPodMallocAlloc
{
	public:
		TArrayPodMallocAlloc(){}
		~TArrayPodMallocAlloc(){}

		void* Alloc(size_t size){return malloc(size);}
		void Free(void* ptr, size_t size){free(ptr);}
		void Swap(TArrayPodMallocAlloc& src){}
};

template<typename TYPE, size_t SIZE, typename ALLOC=TArrayPodAlloc>
class TArrayPod
{
	private:
		typedef TArrayPod<TYPE, SIZE, ALLOC> self_type;

		ALLOC 			m_Alloc;
		TYPE			 m_Stack[SIZE];
		TYPE* 			m_pData;
		size_t 		 	m_nCapacity;
		size_t 			m_nSize;

	public:
		TArrayPod()
		{
			m_pData = m_Stack;
			m_nCapacity = SIZE;
			m_nSize = 0;
		}

		TArrayPod(const self_type& src)
		{
			m_nSize = src.m_nSzie;
			if(m_nSize <= SIZE)
			{
				m_pData = m_Stack;
				m_nCapacity = SIZE;
			}
			else
			{
				m_nCapacity = src.m_nCapacity;
				m_pData = (TYPE*)m_Alloc.Alloc(sizeof(TYPE)*m_nCapacity);
			}
			memcpy(m_pData, src.m_pData, m_nSize*sizeof(TYPE));
		}

		~TArrayPod()
		{
			if(m_nCapacity > SIZE)
			{
				m_Alloc.Free(m_pData, sizeof(TYPE)*m_nCapacity);
			}
		}

		self_type& operator=(const self_type& src)
		{
			self_type temp(src);
			swap(temp);
			return *this;
		}

		void swap(self_type& src)
		{
			size_t temp_size = src.m_nSzie;
			size_t temp_capacity = src.m_nCapacity;
			TYPE* temp_pdata = src.m_pData;
			TYPE temp_stack[SIZE];

			if(temp_capacity <= SIZE)
			{
				memcpy(temp_stack, src.m_Stack, temp_size*sizeof(TYPE));
			}

			src.m_nSize = m_nSize;
			src.m_nCapacity = m_nCapacity;

			if(m_nCapacity<=SIZE)
			{
				memcpy(src.m_Stack, m_Stack, m_nSize*sizeof(TYPE));
				src.m_pData = src.m_Stack;
			}
			else{
				src.m_pData = m_pData;
			}

			m_nSize = temp_size;
			m_nCapacity = temp_capacity;

			if(temp_capacity <= SIZE)
			{
				memcpy(m_Stack, temp_stack, temp_size*sizeof(TYPE));
				m_pData = m_Stack;
			}
			else{
				m_pData = temp_pdata;
			}

			m_Alloc.Swap(src.m_Alloc);
		}
};

#endif