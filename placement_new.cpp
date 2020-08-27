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
	const int SIZE = 5;
	// if we know what are the actual values we can use uniform initialization 
	// (C++11 needed) in order to avoid the temporary objects and unnecessary calls
	// to the default constructor as well as asignment
	//Reporter r[SIZE]{1,2,3,4,5};

	// if we want to create the Reporter objects on the heap
	// we see that only the constructor is called and not the destructor
	//Reporter *r1 = new Reporter [SIZE]; 
	
	// if we want to initialize the values inside of r1 we need to do a loop
	/*for (int i = 0 ; i < SIZE; ++i)
	{
		// this line of code will cause in creating a temporary object
		// constructed with the parameterized constructor; then this temporary will be
		// asigned using the asignment operator to r1 before calling the destructor
		r1[i] = Reporter{i};
	}*/
	

	// so in order to avoid the asignment and we know the values we can use
	// uniform initialization with new expressions
	//Reporter *r2 = new Reporter [SIZE] {1,2,3,4,5};

	// we need to manually delete
	//delete[] r1;
	//delete[] r2;


	// if we don't know the values and we still it on the heap without any asignments
	// we need to invoke operator new function on our own
	Reporter *r3 = static_cast<Reporter*>(operator new (SIZE * sizeof(Reporter))) ;

	for (int i = 0; i < SIZE; ++i)
	{
		// (r3 + i) --> this calculation is needed so we can iterate over the 
		// allocated memory and then put the Reporter objects in there
		// the address will increase with the size of the object
		new(r3 + i) Reporter{i};
	}

	// calling placement new we need to invoke a destructor also
	// but calling delete keyword on the r3 pointer will not call the destructors of 
	// the Reporter class; the reason we use operator new function to allocate
	// so we need manually to invoke the destructors of every object in the array
	// and the delete the pointer
	for (int i = 0; i < SIZE; ++i)
	{
		r3->~Reporter();
	}
	operator delete (r3);	


}
