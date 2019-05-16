#include "MagicSquare.h"

int main() {
	std::vector<std::vector<int>> square;//build a 2D vector
	std::cin >> square; //let the user enter the 2D vector
	MagicSquare m(square); //construct a MagicSquare object
	std::cout << '\n';
	m.solveSquare(0);//call solve square function
	std::cout << "Solving Complete!\nThere were " << m.get_count() << " of solutions!\n";//get the number of correct solutions

	return 0;
}