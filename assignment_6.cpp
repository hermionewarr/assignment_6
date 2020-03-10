// PHYS 30762 Programming in C++
// Assignment 6

// A matrix class - Hermione Warr

// Note: for longer functions, you are advised to prototype them
// within class and put the function code itself immediately below class. 

#include<iostream>
//#include<stdlib> // for c style exit

class matrix
{
	// Friends
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat);
	//friend std::istream& operator>>(std::istream& is, const matrix& mat);
private:
	double *matrix_data{ nullptr };
	size_t rows{ 0 };
	size_t columns{ 0 };
	size_t size{ rows * columns };
public:
	// Default constructor
	matrix() = default;
	// Parameterized constructor
	matrix(size_t number_of_rows, size_t number_of_columns);
	// Copy constructor
	matrix(matrix&);
	// Move constructor
	matrix(matrix&&);
	// Destructor
	~matrix() { delete matrix_data; std::cout << "destructor called" << std::endl; };

	// Access functions
	size_t get_rows() const { return rows; } // Return number of rows
	size_t get_columns() const { return columns; } // Return number of columns
	size_t get_size() const { return size; }
	double& operator[](size_t i);
	// Return position in array of element (m,n)
	int index(int m, int n) const
	{
		if (m > 0 && m <= rows && n > 0 && n <= columns) {return (n - 1) + (m - 1) * columns;}
		else { std::cout << "Error: out of range" << std::endl; exit(1); }
	}
	double &operator()(size_t m,size_t n) { return matrix_data[index(m, n)]; }
 
	// Deep Copy Assignment operators
	matrix &operator=(matrix&);
	// Move Assignment operator uses rvalues and lvalues
	matrix &operator=(matrix&&);
	// Addition, subtraction and multiplication

	// minor

	// determinant

};

// Member functions defined outside class
//paramerterised constructor
matrix::matrix(size_t number_of_rows, size_t number_of_columns) {
	rows = number_of_rows;
	columns = number_of_columns;
	matrix_data = new double[size];
	for (size_t i{}; i < size; i++) {
		matrix_data[i] = 0;
	}
}
//copy constructor
matrix::matrix(matrix &copymatrix)
{
	matrix_data = nullptr; 
	rows = copymatrix.get_rows();
	columns = copymatrix.get_columns();
	size = copymatrix.get_size();
	if (size > 0) {
		matrix_data = new double[size];
		//copy values into new array
		for (size_t i{}; i < size; i++) {
			matrix_data[i] = copymatrix[i];
		}
	}
}
//move constructor
matrix::matrix(matrix&& movematrix)
{//steal the data
	std::cout << "move constructor" << std::endl;
	size = movematrix.get_size();
	rows = movematrix.get_rows();
	columns = movematrix.get_columns();
	movematrix.size = 0;
	movematrix.matrix_data = nullptr;
}
//assignment op for deep copying
matrix& matrix::operator=(matrix& copymatrix) 
{
	if (&copymatrix == this) return *this;// so self assignment
	//first delete this objects array
	delete[] matrix_data; 
	matrix_data = nullptr; 
	size = 0; rows = 0; columns = 0;
	//now copy size and declare new array
	size = copymatrix.get_size(); rows = copymatrix.get_rows(); columns = copymatrix.get_columns();
	if (size > 0) 
	{
		matrix_data = new double[size];
		//copy values into new array
		for (size_t i{}; i < size; i++)
		{
			matrix_data[i] = copymatrix[i];
		}
	}
	return *this;
}
//assingment op for moving
matrix& matrix::operator=(matrix&& movematrix) 
{
	std::cout << "move aasingment" << std::endl;
	std::swap(size, movematrix.size);
	std::swap(matrix_data, movematrix.matrix_data);
	return *this;
}
//overloaded element [] operator implementation
double& matrix::operator[](size_t i) {
	if (i < 0 || i >= size) {
		std::cout << "Error: trying to access array element out of bounds" << std::endl;
		throw("Out of Bounds Error");
	}
	return matrix_data[i];
}
// Overload insertion to output stream for matrices
std::ostream& operator<<(std::ostream& os, const matrix &mat)
{
	// Code goes here
	for (size_t i{}; i < mat.get_size(); i++) {// do some index shit
		//os << ;
	}
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