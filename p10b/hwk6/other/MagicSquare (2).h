#ifndef _MAGICSQUARE_
#define _MAGICSQUARE_
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

//free functions

/**
an overloaded operator >> to read from a stream into a std::vector<std::vector<int>>
@param1 input reference to std::istream
@param2 new_square the 2-D vector
return std::istream&
*/
std::istream& operator>>(std::istream& input, std::vector<std::vector<int>>& new_square);

/**
an overloaded operator << to write a std::vector<std::vector<int>> with output stream
@param1 output reference to std::ostream
@param2 new_square the 2-D vector
return std::ostream&
*/
std::ostream& operator<<(std::ostream& output, const std::vector<std::vector<int>>& new_square);

class MagicSquare {
private:
	std::vector<std::vector<int>> square; //a private member variable square which is a 2D vector
	std::set<int> used_up; //a set that stored the value that has been used already in the matrix
	std::set<int> position_taken; //a set that stored the position that has been taken in the matrix
	int count=0;//number of valid solutions, first set to 0

public:
	MagicSquare(std::vector<std::vector<int>> _square) : square(std::move(_square)) {  } //constructor

	/**
	This is a helper function that returns the private variable square in a MagicSquare class
	@return square a private variable in MagicSquare of type std::vector<std::vector<int>>
	*/
	std::vector<std::vector<int>> get_square() const {
		return square;
	}

	/**
	This is a function that returns a position # of a number in the square
	@param1 row the row# of the number in the square
	@param2 col the col# of the number in the square
	@return the position
	*/
	int position(size_t row, size_t col) {
		int pos = square.size()*row + col;
		return pos;
	}

	/**
	This is a helper function that returns the count of the correct solutions, which is a private variable
	@return count
	*/
	int get_count() {
		return count;
	}



	/**
	This function checks if a given position in the magic square is empty
	@param1 row of the 2-D vector of type size_t
	@param2 col of the 2-D vector of type size_t
	@return a bool
	*/
	bool empty(size_t row, size_t col) {
		if (square[row][col] == 0) { return true; }//if the position is 0, it is empty
		else { return false; }
	}


	/**
	This function checks if a given number is already used in the magic square
	@param1 int the number
	@return a bool
	*/
	bool taken(int num) {
		for (size_t i = 0; i < square.size(); ++i) {//go through each row
			for (size_t j = 0; j < square.size(); ++j) {//in every row, go through every number of the col in that row
				if (num == square[i][j]) {  // if the given number is equal to a number that's already in the matrix
					return true; 
				}
			}
		}
		return false;
	}

	/**
	This function checks that, after each row is filled, if the square could potentially be valid
	it will check that the sum of each row is the target sum S and that the sum of each partially filled col <= S
	@return a bool
	*/
	bool checkRow() {
		const size_t n = square.size();
		const int targetSum = n * (pow(n, 2) - 1) / 2;
		bool valid_row = false;
		for (size_t row = 0; row < n;++row) {// go through each row
			int row_sum = 0;// first set the sum of the row to 0
			for (size_t col = 0; col < n; ++col) { //go through every col
				if (!empty(row, col)) { row_sum += square[row][col]; } //if the term is not empty, add it to the sum
				else { row_sum = 0; }//if any of the term in this row is empty, this row is not filled, set the sum back to 0
			}
			if (row_sum == targetSum || row_sum == 0) { valid_row = true; }//if the row is filled and satisfies the expected sum or if the row is not filled
			else { //otherwise it cannot be a potentially valid solution
				valid_row = false; 
				break;
			}
		}
		//check the sum of the cols to see if it is less or equal to the expected sum
		bool potential_col = false;
		for (size_t col = 0; col < n; ++col) {//go through each col
			int col_sum = 0;
			for (size_t row = 0; row < n; ++row) {//go through the terms in the same col
				col_sum += square[row][col];//sum the terms, add to the col_sum
			}
			if (col_sum <= targetSum) { potential_col = true; }//if col_sum is less than or equal to the target sum
			else { 
				potential_col = false;
				break;
			}
		}
		if (valid_row&&potential_col) { return true; } //if satisfies both conditions: filled row sum matches the target sum and col sum is currently less or equal too target sum
		else { return false; }
	}

	/**
	This function checks if a complete magic square satisfies the the magic square satidfies the conditions to be a solution
	@return a bool
	*/
	bool checkValid() {
		const size_t n = square.size();
		const int targetSum = n * (n*n + 1) / 2;
		//check sum of each row
		for (size_t row = 0; row < n; ++row) {//go through every row
			int row_sum = 0;
			for (size_t col = 0; col < n; ++col) {//go through every term in the same row
				row_sum += square[row][col];
			}
			if (row_sum != targetSum) { return false; }// if the sum of the row does not match the target sum, return false
		}
		//check sum of each col
		for (size_t col = 0; col < n; ++col) {//go through every col
			int col_sum = 0;
			for (size_t row = 0; row < n; ++row) {// go through every row
				col_sum += square[row][col];
			}
			if (col_sum != targetSum) { return false; }//if the sum of the col does not match the target sum, return false
		}
		//check sum of diag
		int diag_sum1 = 0, diag_sum2 = 0;
		for (size_t row = 0; row < n; ++row) {
			diag_sum1 += square[row][row];//the left to right diag
			diag_sum2 += square[row][n - row - 1];//the right to left diag
		}
		if (diag_sum1 != targetSum || diag_sum2 != targetSum) {//if either one of the diag sum does not equal to the target sum, return false
			return false;
		}
		return true;//when the sum of the row, col, and diag all matches the target sum
	}
	
	/**
	This is a recursive solve square function
	@param index tracking the number of slots we already went over
	*/
	void solveSquare(int index) {
		size_t sz = square.size(); // set sz to be the dimension of the square
		size_t spots_total = sz * sz; // the number of total spots is sz*sz

		if (index == 0) {//when the index is 0 at the beginning
			//looping through every row and col
			for (size_t i = 0; i < sz;++i) {
				for (size_t j = 0; j < sz; ++j) {
					if (!empty(i, j)) {//if the position is not empty( not 0)
						used_up.insert(square[i][j]);//insert the number into the set of used up values
						position_taken.insert(position(i, j));//insert the position of the number into the set of position taken
					}
				}
			}
		}

		if (index == spots_total) {
			if (checkValid()) {//if the solution is valid
				++count;//increment the count of the valid solution by 1
				std::cout << square; //print it
				std::cout << '\n';

			}
		}
		else {
			size_t row = (index / sz);//set the row# of the term that we are traking
		    size_t col = (index%sz);//set the col# of the term that we are tracking
			if (empty(row, col)) {//if the term is empty
				for (int i = 1; i <= spots_total; ++i) {//try every possible number that could be appeared in this matrix
					if (!taken(i)) {//if the number has not been taken
						square[row][col] = i;//set the empty term to i
						solveSquare(index + 1);//call this function again
						square[row][col] = 0;//finally set it back to 0 and plug in another value and start the process again
					}
				}
			}
			else {//if the term is not empty, track the next term
				solveSquare(index + 1);
			}
		}

	}

};



#endif
