#include <iostream>


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

	std::cout << "Done" << std::endl;
}
