#include <iostream>
#include <malloc.h>
#include <exception>
#include <climits>
#include <thread>

int g_value; // global value ----> stored in data segment
	     // of the virtual address space

int* a_ptr[5]{};

// handler if operator new functions fail
void NewHandler()
{
	std::cout << "Failed to allocate memory" << std::endl;

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
	delete [] a_ptr[0];
	a_ptr[0] = nullptr;
}

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


	// C++ dynamic allocation 
	// dynamically allocating with initialization - array
	// NOTE: new keyword invokes the operator new function that allocates the memory
	// and then if we call it for a custom class it invokes the constructor of that
	// class or initialize the memory and then returns the memory adress 
	int* ptr = new int[7]{1,2,3,4,5};
	for (int i =0; i < 7 ; ++i)
	{
		std::cout << ptr[i] << " " << std::endl;
	}

	delete [] ptr;
	
        
	// second way to handle a new fail : handlerer
	//std::set_new_handler(NewHandler);
	
        // we will try to make new fail with standard behaivior :       
        // it will throw a exception
	try
        {
                for (int i = 0; i < 5; ++i)
                {
                        std::cout << "Allocating memory #" << i << std::endl;
                        a_ptr[i] = new int[INT_MAX/2];
                        std::cout << "Success!" << std::endl;
                }
        }
        catch (std::exception& ex)
        {
                std::cout << "Exception: " << ex.what() << std::endl;
        }


	// nothrow new expression
	int* nothrow_p = new (std::nothrow) int[INT_MAX];
	// using std::nothrow the new expression will return nullptr if 
	// the allocation fails
	if (nothrow_p == nullptr)
	{
		std::cout << "Nothrow new: failed to allocate memory." << std::endl;
		return -1;
	}

	delete nothrow_p;
	std::cout << "Done" << std::endl;
}
