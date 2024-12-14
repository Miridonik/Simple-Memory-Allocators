#pragma once
#include "includes.h"
#include <assert.h>
#include "List.h"

class PoolAllocator
{
public:
	PoolAllocator() = delete;
	PoolAllocator(const std::size_t totalSize, const std::size_t block_size);
	~PoolAllocator();
	void Create();
	void* Allocate(const std::size_t size);
	void Destroy();
	void Free();
	void Deallocate(void* ptr);
	std::size_t GetSizeOfUsedMem();
private:
	List free_list;
	void* p_start = nullptr;
	void* p_end = nullptr;
	std::size_t total_size = 0;
	std::size_t block_size = 0;
	//std::size_t offset = 0;
	std::size_t used = 0;
};


