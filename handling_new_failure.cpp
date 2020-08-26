#include <iostream>
#include <exception>
#include <climits>
#include <thread>

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
	// Dynamic allocation 
	// NOTE: dynamic memory can be accessed throughout the program
	// as long as you have the address. But the lifetime of the memory
	// needs to be managed manually.
	// Reasons for using dynamic memory: not knowing what size you will
	// need at compile time or you need more control over the lifetime
	// of the data
	
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


	// third way of handling it is using nothrow new expression
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
