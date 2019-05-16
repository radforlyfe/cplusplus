//
//  main.cpp
//  assignment6

#include "MagicSquare.h"

/**
 overloaded operator>>
 @param1 in - stream
 @param2 square vector of vector of int
 @return stream&
 */
std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& square){
    int value = 0;
    for(size_t i = 0; i < square.size(); ++i){
        for(size_t j = 0; j < square.size(); ++j){
            if(in >> value){
                square[i][j] = value;
            }
            else if(in.fail()){
                in.clear();
                in.ignore();
            }
        }
    }
    return in;
}

/**
 overloaded operator<<
 @param1 out output stream
 @param2 square vector of vector of int
 @return stream&
 */
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& square){
    for(size_t i = 0; i < square.size(); ++i){
        for(size_t j = 0; j < square.size(); ++j){ // how to do size of the inner vector?
            out << square[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

int main(){
    std::cout << "Enter a square size: ";
    size_t square_size;
    std::cin >> square_size;
    std::vector<std::vector<int>> msquare(square_size, std::vector<int>(square_size));
    std::cout << "Enter a square format: \n";
    std::cin >> msquare;
    std::cout << msquare;
    MagicSquare s(msquare);
    s.solveSquare(0);
    std::cout << "Solving complete! \n";
    std::cout << "There were " << s.getcount() << " solutions! \n";
    return 0;
}
