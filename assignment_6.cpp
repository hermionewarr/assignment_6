// PHYS 30762 Programming in C++
// Assignment 6
// A matrix class - Hermione Warr

#include<iostream> 

class matrix
{
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat);
	friend std::istream& operator>>(std::istream& is, matrix& mat_input);
private:
	double *matrix_data{ nullptr };
	size_t rows{ 0 };
	size_t columns{ 0 };
public:
	// Default and Parameterised constructors
	matrix() = default;
	matrix(size_t number_of_rows, size_t number_of_columns);
	// Copy constructor
	matrix(matrix&);
	// Move constructor
	matrix(matrix&&) noexcept;
	// Destructor
	~matrix() { delete matrix_data; std::cout << "destructor called" << std::endl; };
	// Access functions
	size_t get_rows() const { return rows; } // Return number of rows
	size_t get_columns() const { return columns; } // Return number of columns
	double& operator[](size_t i) const;
	// Return position in array of element (m,n)
	int index(size_t m, size_t n) const {
		if (m > 0 && m <= rows && n > 0 && n <= columns) { return (n - 1) + (m - 1) * columns; }
		else { std::cout << "Error: out of range" << std::endl; exit(1); }
	}
	double &operator()(size_t m,size_t n) const { return matrix_data[index(m, n)]; } 
	// Deep Copy Assignment operators
	matrix& operator=(matrix&);
	// Move Assignment operator uses rvalues and lvalues
	matrix& operator=(matrix&&) noexcept;
	// Addition, subtraction and multiplication
	matrix operator+(matrix& matrix_to_add);
	matrix operator-(matrix& matrix_to_minus);
	matrix operator*(matrix& matrix_to_multiply);
	// minor
	matrix minor(size_t row_to_delete, size_t column_to_delete);
	// determinant
	double determinant();
};
/*-------------------------------------
Member functions defined outside class
--------------------------------------*/
//paramerterised constructor
matrix::matrix(size_t number_of_rows, size_t number_of_columns) 
{
	rows = number_of_rows;
	columns = number_of_columns;
	matrix_data = new double[rows*columns];
	for (size_t i{}; i < rows*columns; i++) {
		matrix_data[i] = 0;
	}
}
//overloaded element [] operator implementation
double& matrix::operator[](size_t i) const
{
	if (i < 0 || i >= rows * columns) {
		std::cout << "Error: trying to access array element out of bounds" << std::endl;
		throw("Out of Bounds Error");
	}
	return matrix_data[i];
}
//copy constructor
matrix::matrix(matrix &copymatrix)
{
	std::cout << "copy constructor called\n";
	matrix_data = nullptr; 
	rows = copymatrix.get_rows();
	columns = copymatrix.get_columns();
	if (rows*columns > 0) {
		matrix_data = new double[rows*columns];
		//copy values into new array
		for (size_t i{}; i < rows*columns; i++) {
			matrix_data[i] = copymatrix[i];
		}
	}
}
//move constructor
matrix::matrix(matrix &&movematrix) noexcept
{  
	std::cout << "move constructor called" << std::endl;
	rows = movematrix.rows;
	columns = movematrix.columns;
	matrix_data = movematrix.matrix_data;
	movematrix.rows = 0;
	movematrix.columns = 0;
	movematrix.matrix_data = nullptr;
}
//assignment operator for deep copying
matrix& matrix::operator=(matrix &copymatrix)
{
	std::cout << "copy assignment operator called \n";
	if (&copymatrix == this) return *this;// so self assignment
	//first delete this objects array
	delete[] matrix_data; 
	matrix_data = nullptr; 
	rows = 0; columns = 0;
	//now copy size and declare new array
	rows = copymatrix.get_rows(); columns = copymatrix.get_columns();
	if (rows*columns > 0) {
		matrix_data = new double[rows*columns];
		//copy values into new array
		for (size_t i{}; i < rows*columns; i++){
			matrix_data[i] = copymatrix[i];
		}
	}
	return *this;
}
//assingment operator for moving
matrix& matrix::operator=(matrix&& movematrix) noexcept
{
	std::cout << "move aasingment operator called" << std::endl;
	std::swap(rows, movematrix.rows);
	std::swap(columns, movematrix.columns);
	std::swap(matrix_data, movematrix.matrix_data);
	return *this;
}
//Addition
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
	else {std::cout << "ya fucked it\n"; exit(1);}
}
//Subbtration
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
	else { std::cout << "ya fucked it\n"; exit(1); }
}
//Multiplication
matrix matrix::operator*(matrix& matrix_to_multiply) 
{
	if (columns == matrix_to_multiply.rows) 
	{
		matrix multiplied_matrix{ rows, matrix_to_multiply.columns };
		for (size_t i{1}; i <= rows; i++) {
			for (size_t j{1}; j <= columns; j++) {
				for (size_t k{1}; k <= matrix_to_multiply.rows; k++) {//matrix_data[index(i,k)]
					multiplied_matrix(i,j) += (*this)(i,k) * matrix_to_multiply(k,j);
				}
			}
		}
		return multiplied_matrix;
	}
	else { std::cout << "you cannot multiply these two matrices together" << std::endl; exit(1);}
}
//Minor
matrix matrix::minor(size_t row_to_delete, size_t column_to_delete) 
{
	matrix minor(rows-1,columns-1); 
	if (row_to_delete <= rows && column_to_delete <= columns && rows >1 && columns >1) {
		for (size_t i{ 1 }; i <= rows; i++) {
			for (size_t j{ 1 }; j <= columns; j++) {
				if (i < row_to_delete && j < column_to_delete) {
					minor(i, j) = (*this)(i, j);
				}
				else if (i > row_to_delete && j > column_to_delete) {
					minor(i - 1, j - 1) = (*this)(i, j);
				}
				else if (i < row_to_delete && j > column_to_delete) {
					minor(i, j - 1) = (*this)(i, j);
				}
				else if (i > row_to_delete && j < column_to_delete) {
					minor(i - 1, j) = (*this)(i, j);
				}
			}
		}
	}
	else { std::cout << "invalid row or column entered" << std::endl; exit(1); }
	return minor;
}
//Determinant
double matrix::determinant() {
	if (rows == columns) {
		std::cout << "Calculating the determinant..." << std::endl;
		double det{};
		if (rows * columns > 4) {
			for (size_t j{1}; j <= columns; j++) {
				det += pow(-1,1+j)*((*this)(1,j))*(minor(1,j).determinant());
			}
			return det;
		}
		else if (rows * columns == 4) {
			double det = ((*this)(1,1) * (*this)(2, 2) - (*this)(2, 1) * (*this)(1, 2));
			return det;
		}
	}
	else { std::cout << "cannot calculate determinant" << std::endl; exit(1); }
}
/*----------------------------------------------------
Overload friend operators for output and input stream
-----------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const matrix& mat)
{
	os << "[";
	for (size_t i{ 1 }; i <= mat.rows; i++) {
		for (size_t j{ 1 }; j <= mat.columns; j++) {
			os << mat(i, j);
			if (j != mat.columns) { os << "   "; }
		}
		if (i != mat.rows) { os << std::endl; }
	}
	os << "]\n";
	return os;
}
std::istream& operator>>(std::istream& is, matrix& mat_input) {
	std::cout << "please enter you matrix data as elements seperated by space: " << std::endl;
	for (size_t i{}; i < mat_input.rows * mat_input.columns; i++) {
		is >> mat_input.matrix_data[i];
	}
	return is;
}
/*------------
Main program
------------*/
int main()
{
	/*----------------------------------------------------------------
	First part of assignment: constructing, deep copying and matrices
	-----------------------------------------------------------------*/
	//Default constructor
	matrix a1;
	std::cout <<"Default constructor a1: \n" << a1;
	//Parameterized constructor
	const int m{ 2 };
	const int n{ 2 };
	matrix a2{ m,n };
	//Set values print a2
	a2[0] = 1; a2[1] = 3;
	a2[2] = 2; a2[3] = 9;
	std::cout << "a2:\n" << a2;;
	//Deep copy by assignment: define new matrix a3 then copy from a2 to a3 and self assign a3
	matrix a3{ m,n };
	std::cout << "empty a3:\n" << a3;
	a3 = a2;
	std::cout << "a2 copied by assignment to a3:\n" << a3;
	a3 = a3;
	std::cout << "self assigning a3:\n" << a3;
	//Modify contents of a2 matrix and show assigned matrix is unchanged here
	a2[1] = 2;
	std::cout << "modified a2:\n" << a2;
	std::cout << "unchanged a3:\n" << a3;
	//Deep copy using copy constructor l
	matrix a4{ a2 };
	std::cout << "deep copy of modified a2 to a4:\n" << a4;
	// Modify contents of original matrix and show copied matrix is unchanged here
	a2(1, 2) = 5;
	std::cout << "a2 modified again:\n" << a2;
	std::cout << "unchanged a4:\n" << a4;
	//Move construction demonstration
	matrix a5(std::move(a2));
	std::cout <<"move a2 to a5: \n"  << a5;
	// Move assignment demonstration
	matrix a6;
	a6 = std::move(a3);
	std::cout <<"move a3 to a6 by assignment \na6 = \n"<< a6;
	//input a matrix
	size_t input_matrix_rows{};
	size_t input_matrix_columns{};
	std::cout << "Please enter the rows for your matrix: " << std::endl;
	std::cin >> input_matrix_rows;
	std::cout << "Please enter the columns for your matrix: " << std::endl;
	std::cin >> input_matrix_columns;
	matrix a_in{ input_matrix_rows,input_matrix_columns };
	std::cin >> a_in;
	std::cout << "a_in:\n" << a_in;
	/*-------------------------------------------------
	Second part of assignment:matrix addition, 
	subtraction, multiplication, minors and determinants
	---------------------------------------------------*/
	matrix b1{ 2,2 };
	matrix b2{ 2,2 };
	matrix b3{ 3,3 };
	matrix b4{ 4,4 };
	//b1
	b1[0] = 5; b1[1] = 2; 
	b1[2] = 3; b1[3] = 4;
	//b2
	b2[0] = 4; b2[1] = 2;
	b2[2] = 1; b2[3] = 3;
	//b3
	b3[0] = 5; b3[1] = 2; b3[2] = 3; 
	b3[3] = 4; b3[4] = 2; b3[5] = 9; 
	b3[6] = 1; b3[7] = 8; b3[8] = 2;
	//b4
	b4[0] = 5; b4[1] = 2; b4[2] = 3; b4[3] = 4; 
	b4[4] = 2; b4[5] = 9; b4[6] = 1; b4[7] = 8; 
	b4[8] = 2; b4[9] = 1; b4[10] = 2; b4[11] = 1;
	b4[12] = 2; b4[13] = 1; b4[14] = 2; b4[15] = 2;
	// Addition of 2 matrices
	std::cout << "b1 + b2 = \n" << b1+b2;
	// Subtraction of 2 matrices
	std::cout << "b2 - b1 = \n" << b2-b1;
	// Multiplication of 2 matrices
	std::cout << "b2 * b1 = \n" << b2 * b1;
	// Minor
	std::cout << "The minor of b3 with row 2 and column 1 deleted is:\n" << b3.minor(2, 1) << std::endl;
	// Determinant
	std::cout << "The determinant of a 3 by 3 matrix b3 is: \n" << b3.determinant() << std::endl;
	std::cout << "The determinant of a 2 by 2 matrix b2 is:\n" << b2.determinant() << std::endl;
	std::cout << "4 by 4 matrix determinant:\n" << b4.determinant() <<std::endl;
	return 0;
}