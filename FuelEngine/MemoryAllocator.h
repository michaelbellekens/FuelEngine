#pragma once
namespace fuel
{
	class MemoryAllocator
	{
	public:
		virtual ~MemoryAllocator() = default;

		virtual void Reset() = 0;
		virtual void* Acquire() = 0;

		virtual size_t GetFreeSpaceAmount() const = 0;
		virtual size_t GetHashOfStoredType() const = 0;
		virtual size_t GetNumOfStoredElements() const = 0;

		// remove default copy & move constructors/assignment operators
		MemoryAllocator(const MemoryAllocator&) = delete;
		MemoryAllocator(MemoryAllocator&&) = delete;
		MemoryAllocator& operator= (const MemoryAllocator&) = delete;
		MemoryAllocator& operator= (const MemoryAllocator&&) = delete;

	protected:
		MemoryAllocator() = default;
	};
}

