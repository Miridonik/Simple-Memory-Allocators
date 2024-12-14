#pragma once
#include "Utils.h"
#include "includes.h"
#include <assert.h>
class LinearAllocator
{
public:
	LinearAllocator() = delete;
	LinearAllocator(const std::size_t totalSize);
	~LinearAllocator();
	void Create();
	void* Allocate(const std::size_t size, const std::size_t alignment = 0);
	void Free();
	void Destroy();
	std::size_t GetSizeOfUsedMem();
private:
	void* p_start = nullptr;
	std::size_t total_size = 0;
	std::size_t offset = 0;
	std::size_t used = 0;
};

