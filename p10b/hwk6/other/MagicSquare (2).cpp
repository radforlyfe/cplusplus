#include"MagicSquare.h"

std::istream& operator>>(std::istream& input, std::vector<std::vector<int>>& new_square) {
	size_t size;
	std::cout << "Enter a square size: ";
	std::cin >> size; //prompt the user to enter the dimension of the 2-D vector
	std::cin.ignore();
	if (size == 0) { std::cout << "Invalid square size!"; }
	else {
		std::cout << "Enter square format: \n";
		for (size_t i = 0; i < size; ++i) { //track the number of rows the user inputs
			std::string inputRow;
			std::getline(std::cin, inputRow);
			for (size_t i = 0; i < inputRow.size(); ++i) {
				if (inputRow[i] == '*') { inputRow[i] = '0'; }//if the user input is *, set it to 0
			}
			std::istringstream iss(inputRow); //use a istringstream to get the numbers in the string
			std::vector<int> row;
			while (iss.peek() != -1) {
				int value;
				iss >> value; //read an integer from the istringstream
				row.push_back(value);  //plug each value to the vector row
				iss.get();  //get the space after each number
			}
			new_square.push_back(row); //plug each row vector to the 2-D vector new_square

		}
	}
	return input;
}

std::ostream& operator<<(std::ostream& output, const std::vector<std::vector<int>>& new_square) {
	const size_t dimension = new_square.size();
	for (size_t i = 0; i < dimension; ++i) {//go over each row
		for (size_t j = 0; j < dimension; ++j) {//go over each column
			output << new_square[i][j]; //print out each term
			output << ' '; //and print a white space after each term
		}
		output << '\n';  //after looping through one row prints a newline character
	}
	return output;
}