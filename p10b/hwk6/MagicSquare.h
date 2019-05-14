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
#include<cctype>

class MagicSquare{
private:
    std::vector<std::vector<int>> input_;
    std::unordered_set<int> taken_;
    
public:
    bool empty(size_t row, size_t col) const;
    bool taken(int i) const;
    bool checkRow() const;
    bool checkValid() const;
    void solveSquare(const int& index);
};

std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& square);
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& square);

#endif /* MagicSquare_h */
