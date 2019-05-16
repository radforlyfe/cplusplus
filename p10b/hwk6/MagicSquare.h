//
//  MagicSquare.h
//  assignment6

#ifndef MagicSquare_H
#define MagicSquare_H
#include<vector>
#include<iostream>
#include<sstream>
#include<unordered_set>
#include<string>

std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& square);
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& square);

class MagicSquare{
public:
    /**
     Constructor that accepts a vector of vector of ints
     @param vec is vector of vector of ints
     */
    MagicSquare(const std::vector<std::vector<int>>& vec);
    
    /**
    solves the magic square and calls on CheckRow and CheckValid
     @param index is index
     */
    void solveSquare(size_t index);
    
    /**
     Get the value at the index
     @param index is index
     @return value at the index
     */
    int getnum(size_t index) const;
    
    /**
     Gets the count of solutions
     @return integer of count
     */
    int getcount() const;

private:
    bool empty(size_t row, size_t col) const;
    bool taken(int i);
    bool checkRow() const;
    bool checkValid() const;
    std::vector<std::vector<int>> data_;
    std::unordered_set<int> taken_;
    int count_solutions = 0;
};

#endif /* MagicSquare_h */
