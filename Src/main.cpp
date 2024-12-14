#include "LinearAllocator.h"
#include "PoolAllocator.h";

int main()
{
	//LinearAllocator
	LinearAllocator a1(20);
	a1.Create();
	void* p_mem = a1.Allocate(20);
	//a1.Deallocate() - undefined for this allocator
	a1.Destroy();

	//PoolAllocator
	PoolAllocator a2(8,4);
	a2.Create();	
	void* block1 = a2.Allocate(4);
	void* block2 = a2.Allocate(4);
	a2.Deallocate(block2);
	void* block3 = a2.Allocate(4);
	a2.Destroy();
}