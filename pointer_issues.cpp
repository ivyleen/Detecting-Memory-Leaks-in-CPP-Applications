#include <iostream>
#include <fstream>

void Serialize(int* p)
{
	if (p == nullptr)
	{
		throw std::runtime_error("!!!Pointer not initialized!!!");
	}

        std::ofstream output ("data.dat");

        if (!output)
        {
                std::cout << "Failed to open file." << std::endl;
                return;
        }

        output << *p;
        output.close();
}

int* GetData()
{
        std::cout << "Enter value: " << std::endl;
        int value{};
        std::cin >> value;

	// this is uninitialized value and if the value is > then 100
	// it will stay uninitialized and there is no way for us
	// to check the validity of the address and the program will 
	// crash and not throw an exception as expected in case of 
	// value less then 100
	// it's ok to use uniform initialization to initialize it
        //int* pValue{};
	int* pValue;

        if (value > 100)
        {
                pValue = new int{value};
        }

        return pValue;
}

int main()
{
	try
	{
		int* p = GetData();
		Serialize(p);
		std::cout << "Data serialized." << std::endl;
		delete p;
	}
	catch (std::exception& ex)
	{
		std::cout << "Exception: " << ex.what() << std::endl;
	}
}

