#include <iostream>


class Reporter
{
	int m_data;

public:
	Reporter()
       		{ std::cout << "Default constructor invoked." << std::endl; }
	Reporter(int x) 
		: m_data{x} 
		{ std::cout << "Parameterized constructor invoked." << std::endl; }
	~Reporter() 
		{ std::cout << "Destructor invoked." << std::endl; }

	Reporter& operator= (const Reporter& other)
	{	
		std::cout << "Asignment operator invoked." << std::endl;
		m_data = other.m_data;
		return *this;
	}

};


int main()
{
	// if we know what are the actual values we can use uniform initialization 
	// (C++11 needed) in order to avoid the temporary objects and unnecessary calls
	// to the default constructor as well as asignment
	Reporter r[5]{1,2,3,4,5};

	// if we want to create the Reporter objects on the heap
	// we see that only the constructor is called and not the destructor
	//Reporter *r1 = new Reporter [5]; 
	
	// if we want to initialize the values inside of r1 we need to do a loop
	/*for (int i = 0 ; i < 5; ++i)
	{
		// this line of code will cause in creating a temporary object
		// constructed with the parameterized constructor; then this temporary will be
		// asigned using the asignment operator to r1 before calling the destructor
		r1[i] = Reporter{i};
	}*/
	

	// so in order to avoid the asignment and we know the values we can use
	// uniform initialization with new expressions
	Reporter *r2 = new Reporter [5] {1,2,3,4,5};

	// we need to manually delete
	//delete[] r1;
	delete[] r2;
}
