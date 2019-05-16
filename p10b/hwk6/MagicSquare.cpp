//
//  MagicSquare.cpp
//  assignment6

#include "MagicSquare.h"

//constructor
MagicSquare::MagicSquare(const std::vector<std::vector<int>>& vec): data_(vec){}

bool MagicSquare::empty(size_t row, size_t col) const{
    if(data_[row][col] == 0){ // if value is 0, then return true
        return true;
    }
    return false;
}

bool MagicSquare::taken(int i){
    for(size_t row = 0; row < data_.size(); ++row){ // loop through all rows
        for(size_t col = 0; col < data_.size(); ++col){ //loop through all columns
            if(i == data_[row][col]){
                return true;
            }
        }
    }
    return false;
}

bool MagicSquare::checkRow() const{
    size_t n = data_.size();
    size_t target = n * ((n * n) + 1)/2;
    for(size_t i = 0; i < n; ++i){ //loop through one dimensional row
        int sum_row = 0;
        int sum_col = 0;
        for(size_t j = 0; j < n; ++j){ // loop through columns
            sum_row += data_[i][j];
            sum_col += data_[j][i];
        }
        if(sum_row != target || sum_col >= target){
            return false;
        }
    }
    return true;
}

bool MagicSquare::checkValid() const{
    size_t n = data_.size();
    size_t target = n * (n * n + 1)/2;
    int sum_diag1 = 0;
    int sum_diag2 = 0;
    if(checkRow()){ // if checkRow is valid proceed
        for(size_t i = 0; i < n; ++i){  // loop through the dimension of square
            sum_diag1 += data_[i][i];
            sum_diag2 += data_[i][n - 1 - i];
        }
    }
    if(sum_diag1 != target || sum_diag2 != target){ // if diag is not equal to target return false
        return false;
    }
    return true;
}

int MagicSquare::getnum(size_t index) const{
    size_t i = index / data_.size();
    size_t j = index % data_.size();
    return data_[i][j];
}



int MagicSquare::getcount() const{
    return count_solutions;
}

void MagicSquare::solveSquare(size_t index){
    size_t n = data_.size();
    if(index == n * n){   //base case of recursion step
        if(checkValid()){   // checks if whole square is valid
            ++count_solutions;
            std::cout << data_ << '\n';
        }
    }
    else{  //if index not at last position
        size_t i = index / data_.size();
        size_t j = index % data_.size();
        if(empty(i,j)){  // if value at index is empty
            for(int value = 1; value <= n * n; ++value){ //loop through all index
                if(!taken(value)){ // ensure value not in taken
                    data_[i][j] = value;
                    solveSquare(index+1);
                    data_[i][j] = 0;
                }
            }
        }
        else{ // if not empty
            solveSquare(index+1);
        }
    }
}
