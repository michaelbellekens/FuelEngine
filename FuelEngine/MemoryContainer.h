#pragma once

template<typename T>
class MemoryContainer
{
public:
	explicit MemoryContainer(size_t bufferSize = 50);
	~MemoryContainer();

	void Release();
	void Reset();
	
	// remove default copy & move constructors/assignment operators
	MemoryContainer(const MemoryContainer&) = delete;
	MemoryContainer(MemoryContainer&&) = delete;
	MemoryContainer& operator= (const MemoryContainer&) = delete;
	MemoryContainer& operator= (const MemoryContainer&&) = delete;

	T& Acquire();
	void RemoveFromContainer(const T* other);

	size_t GetCapacity() const;
	size_t GetHashCodeOfStoredType() const;
	size_t GetNumberOfElements() const;

	// Operator overloading
	T& operator[](size_t idx);

private:
	T* m_pBuffer;
	
	size_t m_Capacity;
	size_t m_Size;
	size_t m_HashCodeType;
};

template <typename T>
MemoryContainer<T>::MemoryContainer(size_t bufferSize)
	: m_pBuffer{ nullptr }
	, m_Capacity{ bufferSize }
	, m_Size{ 0 }
	, m_HashCodeType{ typeid(T).hash_code() }
{
	m_pBuffer = new T[m_Capacity];
}

template <typename T>
MemoryContainer<T>::~MemoryContainer()
{
	Release();
}

template<typename T>
void MemoryContainer<T>::Release()
{
	delete[] m_pBuffer;
	m_pBuffer = nullptr;
}

template<typename T>
void MemoryContainer<T>::Reset()
{
	/*for (size_t i{ 0 }; i < m_Size; ++i)
	{
		delete m_pBuffer[i];
		m_pBuffer[i] = nullptr;
	}*/

	delete[] m_pBuffer;
	m_pBuffer = new T[m_Capacity];
}

template <typename T>
T& MemoryContainer<T>::Acquire()
{
	m_pBuffer[m_Size] = T();
	return &m_pBuffer[m_Size];
}

template <typename T>
void MemoryContainer<T>::RemoveFromContainer(const T* other)
{
	for (size_t i{ 0 }; i < m_Size; ++i)
	{
		if (m_pBuffer[i] == other)
		{
			delete m_pBuffer[i];
			m_pBuffer[i] = nullptr;
		}
	}
}

template <typename T>
size_t MemoryContainer<T>::GetCapacity() const
{
	return m_Capacity;
}

template <typename T>
size_t MemoryContainer<T>::GetHashCodeOfStoredType() const
{
	return m_HashCodeType;
}

template <typename T>
size_t MemoryContainer<T>::GetNumberOfElements() const
{
	return m_Size;
}

template <typename T>
T& MemoryContainer<T>::operator[](size_t idx)
{
	T temp = m_pBuffer[idx];
	return temp;
}
