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
	double& operator[](size_t i) const;
	// Return position in array of element (m,n)
	int index(size_t m, size_t n) const;
	double &operator()(size_t m,size_t n) const { return matrix_data[index(m, n)]; } 
	// Deep Copy Assignment operators
	matrix& operator=(matrix&);
	// Move Assignment operator uses rvalues and lvalues
	matrix& operator=(matrix&&);
	// Addition, subtraction and multiplication
	matrix operator+(matrix& matrix_to_add);
	matrix operator-(matrix& matrix_to_minus);
	matrix operator*(matrix& matrix_to_multiply);
	// minor

	// determinant

};
// Member functions defined outside class
//paramerterised constructor
matrix::matrix(size_t number_of_rows, size_t number_of_columns) 
{
	rows = number_of_rows;
	columns = number_of_columns;
	matrix_data = new double[rows*columns];
	for (size_t i{}; i < rows*columns; i++) 
	{
		matrix_data[i] = 0;
	}
}
//retrun the index
int matrix::index(size_t m, size_t n) const
{
	if (m > 0 && m <= rows && n > 0 && n <= columns){return (n - 1) + (m - 1) * columns;}
	else{std::cout << "Error: out of range" << std::endl; exit(1);}
}
//copy constructor
matrix::matrix(matrix &copymatrix)
{
	std::cout << "copy constructor\n";
	matrix_data = nullptr; 
	rows = copymatrix.get_rows();
	columns = copymatrix.get_columns();
	if (rows*columns > 0) 
	{
		matrix_data = new double[rows*columns];
		//copy values into new array
		for (size_t i{}; i < rows*columns; i++) 
		{
			matrix_data[i] = copymatrix[i];
		}
	}
}
//move constructor
matrix::matrix(matrix &&movematrix)
{   //steal the data
	std::cout << "move constructor" << std::endl;
	rows = movematrix.rows;
	columns = movematrix.columns;
	matrix_data = movematrix.matrix_data;
	movematrix.rows = 0;
	movematrix.columns = 0;
	movematrix.matrix_data = nullptr;
}
//assignment op for deep copying
matrix& matrix::operator=(matrix &copymatrix) 
{
	std::cout << "copy assignment \n";
	if (&copymatrix == this) return *this;// so self assignment
	//first delete this objects array
	delete[] matrix_data; 
	matrix_data = nullptr; 
	rows = 0; columns = 0;
	//now copy size and declare new array
	rows = copymatrix.get_rows(); columns = copymatrix.get_columns();
	if (rows*columns > 0) 
	{
		matrix_data = new double[rows*columns];
		//copy values into new array
		for (size_t i{}; i < rows*columns; i++)
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
	std::swap(rows, movematrix.rows);
	std::swap(columns, movematrix.columns);
	std::swap(matrix_data, movematrix.matrix_data);
	return *this;
}
//overloaded element [] operator implementation
double& matrix::operator[](size_t i) const 
{
	if (i < 0 || i >= rows*columns) 
	{
		std::cout << "Error: trying to access array element out of bounds" << std::endl;
		throw("Out of Bounds Error");
	}
	return matrix_data[i];
}
// Overload insertion to output stream for matrices
std::ostream& operator<<(std::ostream& os, const matrix &mat)
{
	os << "[";
	for (size_t i{1}; i <= mat.get_rows(); i++)
	{
		for (size_t j{1}; j <= mat.get_columns(); j++)
		{
			os << mat(i, j);
			if (j != mat.get_columns()){os << "   ";}
		}
		if (i != mat.get_rows()) {os << std::endl;}
	}
	os << "]\n";
	return os;
}
//addition
matrix matrix::operator+(matrix& matrix_to_add) 
{
	if (rows == matrix_to_add.rows && columns == matrix_to_add.columns) 
	{
		matrix added_matrix{ rows, columns };
		added_matrix.rows = rows; added_matrix.columns = columns;
		for (size_t i{}; i < rows * columns; i++) {
			added_matrix.matrix_data[i] = matrix_data[i] + matrix_to_add.matrix_data[i];
		}
		return added_matrix;
	}
	else {std::cout << "ya fucked it\n"; }
}
	
//subbtration
matrix matrix::operator-(matrix& matrix_to_minus) 
{
	if (rows == matrix_to_minus.rows && columns == matrix_to_minus.columns)
	{
		matrix minus_matrix{ rows, columns };
		minus_matrix.rows = rows; minus_matrix.columns = columns;
		for (size_t i{}; i < rows * columns; i++) {
			minus_matrix.matrix_data[i] = matrix_data[i] - matrix_to_minus.matrix_data[i];
		}
		return minus_matrix;
	}
	else { std::cout << "ya fucked it\n"; }
}
//multiplication
matrix matrix::operator*(matrix& matrix_to_multiply) {
	return matrix_to_multiply;
}
// Main program
int main()
{
	// First part of assignment: constructing and deep copying matrices
	// Demonstrate default constructor
	matrix a1;
	//std::cout << a1; //doesnt work
	// Parameterized constructor
	const int m{ 2 };
	const int n{ 2 };
	matrix a2{ m,n };
	// Set values for a2 here
	a2[0] = 1;
	a2[1] = 3;
	a2[2] = 2;
	a2[3] = 9;
	// Print matrix a2
	std::cout << "a2:\n" << a2;;
	//Deep copy by assignment: define new matrix a3 then copy from a2 to a3
	matrix a3{ m,n };
	std::cout << "a3:\n" << a3;
	a3 = a2;
	std::cout << "a3:\n" << a3;
	// Modify contents of original matrix and show assigned matrix is unchanged here
	std::cout << "a2:\n" << a2;
	std::cout << "a3:\n" << a3;
	//Deep copy using copy constructor l
	matrix a4{ a2 };
	std::cout << "a4:\n" << a4;
	// Modify contents of original matrix and show copied matrix is unchanged here
	a2[1, 0] = 5;
	std::cout << "modified a2:\n" << a2;
	std::cout << "a4:\n" << a4;
	//Move copy construction demonstration
	matrix a5(std::move(a2));
	std::cout << a5;
	// Move assignment demonstration
	matrix a6;
	a6 = std::move(a3);
	std::cout << a6;

	// Second part of assignment: matrix operations
	matrix b1{ 2,2 };
	matrix b2{ 2,2 };
	matrix b3{ 2,3 };
	b1[0] = 5; b1[1] = 2; b1[2] = 3; b1[3] = 4;
	b2[0] = 4; b2[1] = 2; b2[2] = 1; b2[3] = 3;
	// Addition of 2 matrices
	std::cout << "adding b2 and b1 gives: \n" << b2+b1;
	// Subtraction of 2 matrices
	std::cout << "subtracting b2 and b1 gives: \n" << b2-b1;
	// Multiplication of 2 matrices


	// Determinant


	return 0;
}