//
//  MagicSquare.cpp
//  assignment6

#include "MagicSquare.h"

std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& square){
    std::vector<int> row;
    std::string line;
    getline(std::cin, line);
    std::istringstream ss(line);
    char temp;
    int number;
    while(ss >> temp)
    {
        if (temp == '*'){
            number = 0;
         }
        else if (isdigit(temp)){
            number = temp - '0';
        }
        row.push_back(number);
    }
    square.push_back(row);
    return in;
}

//std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& square){
//    for(size_t i = 0; i < square.size(); ++i){
//        for(size_t j = 0; j < std::vector<int>.size; ++j){
//            out <<
//        }
//    }
//
//
//}
