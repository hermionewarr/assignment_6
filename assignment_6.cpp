// PHYS 30762 Programming in C++
// Assignment 6

// A matrix class - Hermione Warr

// Note: for longer functions, you are advised to prototype them
// within class and put the function code itself immediately below class. 

#include<iostream>
#include<stdlib> // for c style exit

class matrix
{
	// Friends
	friend std::ostream &operator<<(std::ostream& os, const matrix& mat);
private:
	double* matrix_data{ nullptr };
	int rows{ 0 };
	int columns{ 0 };
public:
	// Default constructor
	matrix() = default;
	// Parameterized constructor
	matrix(int number_of_rows, int number_of_columns) { 
		rows = number_of_rows;
		columns = number_of_columns;
		matrix_data= new double[rows * columns];
	}
	// Copy constructor
	
	// Move constructor

	// Destructor
	~matrix() { delete matrix_data; std::cout << "destructor called" << std::endl; };

	// Access functions
	int get_rows() const { return rows; } // Return number of rows
	int get_columns() const { return columns; } // Return number of columns

	// Return position in array of element (m,n)
	int index(int m, int n) const 
	{
		if (m > 0 && m <= rows && n > 0 && n <= columns) return (n - 1) + (m - 1) * columns;
		else { std::cout << "Error: out of range" << std::endl; exit(1); }
	}
	double& operator()(int m, int n) { return matrix_data[index(m, n)]; }

	// Other access functions go here

	// Other functions 
	// Deep Copy Assignment operator

	// Move Assignment operator uses rvalues and lvalues

	// Addition, subtraction and multiplication

	// minor

	// determinant

};

// Member functions defined outside class
//copy constructor
matrix::matrix(int number_of_rows, int number_of_columns)
{

}


// Overload insertion to output stream for matrices
std::ostream& operator<<(std::ostream& os, const matrix& mat)
{
	// Code goes here

	return os;
}

// Main program

int main()
{

	//
	// First part of assignment: constructing and deep copying matrices
	//

	// Demonstrate default constructor
	matrix a1;
	std::cout << a1;
	// Parameterized constructor
	const int m{ 2 };
	const int n{ 2 };
	matrix a2{ m,n };
	// Set values for a2 here

	// Print matrix a2
	std::cout << a2;
	// Deep copy by assignment: define new matrix a3 then copy from a2 to a3
	matrix a3{ m,n };
	std::cout << a3;
	a3 = a2;
	std::cout << a3;
	// Modify contents of original matrix and show assigned matrix is unchanged here

	std::cout << a2;
	std::cout << a3;


	// Deep copy using copy constructor 
	matrix a4{ a2 };
	std::cout << a4;
	// Modify contents of original matrix and show copied matrix is unchanged here

	std::cout << a2;
	std::cout << a4;

	// Move copy construction demonstration

	// Move assignment demonstration

	//
	// Second part of assignment: matrix operations
	//

	// Addition of 2 matrices

	// Subtraction of 2 matrices

	// Multiplication of 2 matrices


	// Determinant


	return 0;
}