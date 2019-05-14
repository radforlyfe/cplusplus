//
//  main.cpp
//  assignment6

#include "MagicSquare.h"

int main(){
    std::cout << "Enter a square size: ";
    size_t square_size;
    std::cin >> square_size;
    std::cout << "Enter a square format: \n";
    std::vector<std::vector<int>> msquare;
    for(size_t i = 0; i < square_size; ++i){
        std::cin >> msquare;
    }
//    solveSquare(xx);
    std::cout << "Solving complete! \n";
//   std::cout << "There were " << xx << "solutions! \n";
    return 0;
}
