#include "PoolAllocator.h"


PoolAllocator::PoolAllocator(const std::size_t totalSize, const std::size_t block_size)
{
	//assert(block_size > 4);
	assert(totalSize >= block_size);
	assert(totalSize % block_size == 0);
	total_size = totalSize + 4*(totalSize/block_size);
	this->block_size = block_size + 4;
}

void PoolAllocator::Create()
{
	p_start = malloc(total_size);
	p_end = (void*)((std::size_t)p_start + total_size);
	for (std::size_t i = 0; i < (total_size/block_size); i++)
	{
		free_list.push_forward((void*)((std::size_t)p_start + (i*block_size)));
	}
}

void* PoolAllocator::Allocate(const std::size_t size)
{
	assert(p_start != nullptr);	
	assert(size <= block_size-4);
	assert(free_list.Length() > 0);
	void* block = free_list.pop_front();
	used += block_size-4;
	return block;
}

void PoolAllocator::Deallocate(void* ptr)
{
	assert(p_start != nullptr);	
	assert((std::size_t)ptr >= (std::size_t)p_start && (std::size_t)ptr < (std::size_t)p_end);
	assert((std::size_t)ptr % (block_size-4) == 0);
	free_list.push_forward((void*)((std::size_t)ptr - 4));
	used -= block_size-4;
}

void PoolAllocator::Destroy()
{
	free(p_start);
	p_start = nullptr;
}

void PoolAllocator::Free()
{
	if (free_list.Length() == (total_size / block_size))	
		return;
	else 
	{
		free_list.Reset();
		for (std::size_t i = 0; i < (total_size / block_size); i++)
		{
			free_list.push_forward((void*)((std::size_t)p_start + (i * block_size)));
		}
	}
	used = 0;
}

PoolAllocator::~PoolAllocator()
{
	if (p_start != nullptr)
		Destroy();
}

std::size_t PoolAllocator::GetSizeOfUsedMem()
{
	return used;
}
