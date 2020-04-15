#pragma once
#include "MemoryAllocator.h"

namespace fuel
{
	template<typename T>
	class FixedAllocator : public MemoryAllocator
	{
	public:
		FixedAllocator(const int bufferSize, const size_t objectSize, const size_t hashClassType);
		~FixedAllocator();
		
		FixedAllocator(const FixedAllocator& other) = delete;
		FixedAllocator(FixedAllocator&& other) noexcept = delete;
		FixedAllocator& operator=(const FixedAllocator& other) = delete;
		FixedAllocator& operator=(FixedAllocator&& other) noexcept = delete;

		void* Acquire() override;
		void Reset() override;

		size_t GetFreeSpaceAmount() const override;
		size_t GetHashOfStoredType() const override;
		size_t GetNumOfStoredElements() const override;

		// Operator overloading
		T* operator[](size_t idx);

	private:
		T* m_pBuffer;
		T* m_pStartOfBuffer;
		size_t m_FreeSpace;
		size_t m_SizeBuffer;
		size_t m_NumElements;

		size_t m_TypeID;
	};
	
	template<typename T>
	FixedAllocator<T>::FixedAllocator(const int bufferSize, const size_t objectSize, const size_t hashClassType)
		: m_pBuffer{ static_cast<T*>(calloc(bufferSize, objectSize)) }
		, m_pStartOfBuffer{ nullptr }
		, m_FreeSpace{ static_cast<size_t>(bufferSize) }
		, m_SizeBuffer{ static_cast<size_t>(bufferSize) }
		, m_NumElements{ 0 }
		, m_TypeID{ hashClassType }
	{
		// Initialize
		m_pStartOfBuffer = m_pBuffer;
	}

	template <typename T>
	FixedAllocator<T>::~FixedAllocator()
	{
		FixedAllocator<T>::Reset();
		free(m_pStartOfBuffer);
	}

	template <typename T>
	void* FixedAllocator<T>::Acquire()
	{
		// return a pointer to a buffer of requested size
		if (m_FreeSpace == 0)
		{
			throw std::exception("out of memory");
		}

		void* startOfBlock = m_pBuffer;
		
		++m_pBuffer;
		--m_FreeSpace;
		++m_NumElements;
		
		return startOfBlock;
	}

	template<typename T>
	void FixedAllocator<T>::Reset()
	{
		for (size_t idx{ 0 }; idx < m_NumElements; ++idx)
		{
			T* temp = m_pStartOfBuffer + idx;
			temp->~T();
		}
		m_NumElements = 0;
		m_FreeSpace = m_SizeBuffer;
	}

	template <typename T>
	size_t FixedAllocator<T>::GetFreeSpaceAmount() const
	{
		// return the amount of memory that is still free for use.
		return m_FreeSpace;
	}

	template <typename T>
	size_t FixedAllocator<T>::GetHashOfStoredType() const
	{
		return m_TypeID;
	}

	template <typename T>
	size_t FixedAllocator<T>::GetNumOfStoredElements() const
	{
		return m_NumElements;
	}

	template <typename T>
	T* FixedAllocator<T>::operator[](size_t idx)
	{
		return m_pStartOfBuffer + idx;
	}
}
