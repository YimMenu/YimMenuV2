#pragma once
#include "RTTI.hpp"

#include <cstddef>

namespace rage
{
	class sysMemAllocator
	{
	public:
		DEFINE_RAGE_RTTI(rage::sysMemAllocator);
		virtual void SetQuitOnFail(bool) = 0;
		virtual void* Allocate(std::size_t size, std::size_t align, int subAllocator) = 0;
		virtual void* TryAllocate(std::size_t size, std::size_t align, int subAllocator) = 0;
		virtual void Free(void* pointer) = 0;
		virtual void TryFree(void* pointer) = 0;
		virtual void Resize(void* pointer, std::size_t size) = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) const = 0;
		virtual sysMemAllocator* GetAllocator(int allocator) = 0;
		virtual sysMemAllocator* GetPointerOwner(void* pointer) = 0;
		virtual std::size_t GetSize(void* pointer) const = 0;
		virtual std::size_t GetMemoryUsed(int memoryBucket) = 0;
		virtual std::size_t GetMemoryAvailable() = 0;
	};
}