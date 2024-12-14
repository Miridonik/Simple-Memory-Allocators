#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(const std::size_t totalSize)
{
	this->total_size = totalSize;
}

LinearAllocator::~LinearAllocator()
{
	if (p_start != nullptr)
		Destroy();
}

void LinearAllocator::Create()
{
	p_start = malloc(total_size);
}

void* LinearAllocator::Allocate(const std::size_t size, const std::size_t alignment)
{
	assert(p_start != nullptr);
	std::size_t padding = 0;
	std::size_t current_adress_without_alignment = (std::size_t)p_start + offset;
	if (alignment != 0 && current_adress_without_alignment % alignment != 0)
	{
		padding = Utils::CalculatePadding(current_adress_without_alignment, alignment);
	}
	assert(size + padding + offset <= total_size);

	offset += padding;
	std::size_t current_adress_with_alignment = (std::size_t)p_start + offset;
	offset += size;

	used += size;  

	return (void*)current_adress_with_alignment;
}

void LinearAllocator::Free()
{
	offset = 0;
	used = 0;
}

void LinearAllocator::Destroy()
{
	free(p_start);
	offset = 0;
	used = 0;
	p_start = nullptr;
}

std::size_t LinearAllocator::GetSizeOfUsedMem()
{
	return used;
}