#include <iostream>
#include <malloc.h>

int g_value; // global value ----> stored in data segment
	     // of the virtual address space

int main()
{
	// all variables here are stored on the stack
	int value {}; 		 
	
	int *p = & value;	
	
	int *p1 = new int {};	// this memory is allocated on the heap
				// and p1 is pointing to the memory that 
				// is returned by the new expression

	int *p2 = & g_value;	// this pointer points to the data segment

	int (*pFn)() = main;	// this pointer points to the code segment
				// of the virtual address space because 
				// functions are stored in there


	// Dynamic allocation 
	// NOTE: dynamic memory can be accessed throughout the program
	// as lon as you have the address. But the lifetime of the memory
	// needs to be managed manually.
	// Reasons for using dynamic memory: not knowing what size you will
	// need at compile time or you need more control over the lifetime
	// of the data
	
	// C type of allocating dynamically
	// malloc - only allocated memory but not initialized
	int* c_ptr = static_cast<int*>(malloc(sizeof(int)));
	*c_ptr = 7;
	std::cout << "Malloc allocated ptr with value: " << *c_ptr << std::endl;	// free the memory
	free(c_ptr);

	// calloc - allocation and initialization to 0
	int* c_ptr2 = static_cast<int*>(calloc(1, sizeof(int)));
	std::cout << "Calloc allocated ptr with value: " << *c_ptr2 << std::endl;	// free the memory

	// realloc - reallocates the given area of memory
	std::cout << "Size of calloc allocated ptr: " << malloc_usable_size(c_ptr2) << std::endl;
	c_ptr2 = static_cast<int*> (realloc(c_ptr2, sizeof(int) * 100));
	std::cout << "Size of calloc ptr after realloc: " << malloc_usable_size(c_ptr2) << std::endl;
	free(c_ptr2);

	std::cout << "Done" << std::endl;
}
