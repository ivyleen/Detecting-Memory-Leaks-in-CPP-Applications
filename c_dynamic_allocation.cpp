#include <iostream>
#include <malloc.h>

int main()
{

	// Dynamic allocation
	// NOTE: dynamic memory can be accessed throughout the program
	// as lon as you have the address. But the lifetime of the memory
	// needs to be managed manually.
	// Reasons for using dynamic memory: not knowing what size you will
	// need at compile time or you need more control over the lifetime
	// of the data

	// C type of allocating dynamically
	// NOTE: non of these types call the constructor or destructor
	// in allocation of object
	// malloc - only allocated memory but not initialized
	int* c_ptr = static_cast<int*>(malloc(sizeof(int)));
	*c_ptr = 7;
	std::cout << "Malloc allocated ptr with value: " << *c_ptr << std::endl;
	// free the memory
	free(c_ptr);

	// calloc - allocation and initialization to 0
	int* c_ptr2 = static_cast<int*>(calloc(1, sizeof(int)));
	std::cout << "Calloc allocated ptr with value: " << *c_ptr2 << std::endl;

	// realloc - reallocates the given area of memory
	std::cout << "Size of calloc allocated ptr: " << malloc_usable_size(c_ptr2) << std::endl;
	c_ptr2 = static_cast<int*> (realloc(c_ptr2, sizeof(int) * 100));
	// if the reallocation failed it will return a NULL pointer
	if (c_ptr2 != NULL)
		std::cout << "Size of calloc ptr after realloc: " << malloc_usable_size(c_ptr2) << std::endl;
	// free the memory
	free(c_ptr2);
}
